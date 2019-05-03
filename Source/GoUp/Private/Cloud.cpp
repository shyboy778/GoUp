// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Cloud.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Public/Muffin.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

// Sets default values
ACloud::ACloud()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	CloudPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CloudPlane"));
	CloudPlane->SetupAttachment(RootComponent);

	RainPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RainPlane"));
	RainPlane->SetupAttachment(CloudPlane);

	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText"));
	ScoreText->SetupAttachment(RootComponent);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(CloudPlane);
}

// Called when the game starts or when spawned
void ACloud::BeginPlay()
{
	Super::BeginPlay();
	setRandomCloudTexture();
	EnableRain();
}

void ACloud::setRandomCloudTexture()
{
	MatInterface = CloudPlane->GetMaterial(0);
	MatIstance = CloudPlane->CreateDynamicMaterialInstance(0,MatInterface);
	int index = FMath::RandRange(0,2);
	if (Textures[index])
	{
		MatIstance->SetTextureParameterValue(FName(TEXT("Texture")), Textures[index]);
		CloudPlane->SetMaterial(0, MatIstance);
	}
}

void ACloud::DisplayScore()
{
	Muffin->IncreaseScore();
	ScoreText->SetText(FText::FromString(FString::FromInt(Muffin->GetScore())));
}

void ACloud::EnableRain()
{
	//在三个数之间取随机数
	int index = FMath::RandRange(0, 2);
	if (index == 0)
	{
		RainPlane->SetVisibility(true);
	}
	AudioComp->Activate(true);
}

// Called every frame
void ACloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACloud::NotifyActorBeginOverlap(AActor * OtherActor)
{
	//继承父类的方法
	Super::NotifyActorBeginOverlap(OtherActor);
	Muffin = Cast<AMuffin>(OtherActor);
	if (Muffin)
	{
		Muffin->Launch();
		DisplayScore();
		UGameplayStatics::PlaySoundAtLocation(this,CloudSound,GetActorLocation());
		//这个函数用蓝图实现，并且有销毁函数
		FadeOut();

	}
}

