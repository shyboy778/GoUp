// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/GameCamera.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Public/Muffin.h"
#include "Components/BoxComponent.h"
#include "Public/Cloud.h"

// Sets default values
AGameCamera::AGameCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isFollowPlayer = true;
	//组件实例化
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	//绑定组件
	CameraComp->SetupAttachment(RootComponent);
	DestoryArea = CreateDefaultSubobject<UBoxComponent>(TEXT("DestoryArea"));
	DestoryArea->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGameCamera::BeginPlay()
{
	Super::BeginPlay();
	PlayControl = UGameplayStatics::GetPlayerController(this,0);
	PlayControl->SetViewTargetWithBlend(this,0);
	Muffin=Cast<AMuffin>(UGameplayStatics::GetPlayerPawn(this,0));
}

// Called every frame
void AGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isFollowPlayer)
	{
		CameraMove();
		CheckIfFalling();
	}

}
void AGameCamera::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	ACloud* Cloud = Cast<ACloud>(OtherActor);
	if (Cloud)
	{
		Cloud->Destroy();
	}
}
void AGameCamera::CameraMove()
{
	FVector CameraLocation = FVector(GetActorLocation().X,GetActorLocation().Y,Muffin->GetActorLocation().Z);
	SetActorLocation(CameraLocation);
}
void AGameCamera::CheckIfFalling()
{
	if (Muffin->GetVelocity().Z < 0)
	{
		UpdateTimer();
	}
	else
	{
		ResetTimer();
	}
}void AGameCamera::OnSureFalling()
{
	isFollowPlayer = false;
	float OldCameraPosX = GetActorLocation().X;
	float OldCameraPosY = GetActorLocation().Y;
	SetActorLocation(FVector(OldCameraPosX, OldCameraPosY,-30.0f));

	float OldMuffinPosX = Muffin->GetActorLocation().X;
	float OldMuffinPosY = Muffin->GetActorLocation().Y;
	Muffin->SetActorLocation(FVector(OldMuffinPosX, OldMuffinPosY, 100.0f));

	Muffin->DisableInput(PlayControl);
}