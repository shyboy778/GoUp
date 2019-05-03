// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Muffin.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMuffin::AMuffin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LaunchVelocity = FVector(0,0,1500);
	AirSpeed = 3500.0f;
	GroundSpeed = 300.0f;
	
}


// Called when the game starts or when spawned
void AMuffin::BeginPlay()
{
	Super::BeginPlay();
	//通过cast转换，类似蓝图
	PlayControl = Cast<APlayerController>(GetController());
	//显示鼠标
	PlayControl->bShowMouseCursor = true;
	ResetGame();
}

// Called every frame
void AMuffin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!isDeath)
	{
		MoveToTouch();
		MoveToCursor();
		SetSpeed();
	}
}

// Called to bind functionality to input
void AMuffin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&AMuffin::LaunchStart);
}
void AMuffin::MoveToCursor()
{
	FVector MouseLocation, MouseDirection;
	//获取鼠标的世界位置
	PlayControl->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	//对Y坐标的值进行限制
	float YDirection=FMath::Clamp(MouseLocation.Y - GetActorLocation().Y,-1.0f,1.0f);
	FVector Direction = FVector(0,YDirection,0);

	float ScaleValue = FMath::Clamp(FMath::Abs(MouseLocation.Y - GetActorLocation().Y) / 100,0.0f,1.0f);
	AddMovementInput(Direction, ScaleValue);

}
void AMuffin::LaunchStart()
{
	if (!GetCharacterMovement()->IsFalling() && !isGameStarted)
		Launch();
	if (!isGameStarted)
	{
		isGameStarted = true;
	}
	
}

void AMuffin::SetSpeed()
{
	if (GetCharacterMovement()->IsFalling())
	{
		GetCharacterMovement()->MaxWalkSpeed = AirSpeed;
	}
	else
	{
		if (isGameStarted)
		{
			GameOver();
		}
		GetCharacterMovement()->MaxWalkSpeed = GroundSpeed;
	}
}

void AMuffin::GameOver()
{
	isDeath = true;
	SetActorRotation(FRotator::ZeroRotator);
	EnableInput(PlayControl);
	ShowRestart();
}

void AMuffin::ResetGame()
{
	isGameStarted = false;
	Score = 0;
	isDeath = false;
}


void AMuffin::Launch()
{
	LaunchCharacter(LaunchVelocity,false,true);
}

void AMuffin::IncreaseScore()
{
	Score++;
}

int AMuffin::GetScore() const
{
	return Score;
}
