// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/CloudSpawner.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Public/Cloud.h"
#include "Public/Muffin.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACloudSpawner::ACloudSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//自定义一个scene作为根组件
	DefaultRoot= CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SpawnArea->SetupAttachment(RootComponent);

	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerArea"));
	TriggerArea->SetupAttachment(RootComponent);

	//初始化参数
	InitialSpawnAmount = 6;
	SpawnSpacing = 300.0f;
}

void ACloudSpawner::SpawnCloud()
{
	FVector SpawnOrigin = SpawnArea->Bounds.Origin;
	FVector SpawnExtent = SpawnArea->Bounds.BoxExtent;
	float YLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent).Y;
	FVector SpawnLocation = FVector(SpawnArea->GetComponentLocation().X, YLocation, SpawnArea->GetComponentLocation().Z);
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<ACloud>(Cloud, SpawnLocation,FRotator::ZeroRotator, SpawnParameters);

	//云彩生成器的上升
	AddActorWorldOffset(FVector(0,0,SpawnSpacing));

}

void ACloudSpawner::ResetCloud()
{
	InitialSpawnAmount = 6;
	//归零云彩生成器
	SetActorLocation(FVector::ZeroVector);

	TArray<AActor*> FoundClouds;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ACloud::StaticClass(), FoundClouds);
	for (AActor* TActor: FoundClouds)
	{
		ACloud* MyCloud = Cast<ACloud>(TActor);
		if (MyCloud != nullptr)
		{
			MyCloud->Destroy();
		}
	}

	while (InitialSpawnAmount>0)
	{
		SpawnCloud();
		InitialSpawnAmount--;
	}
}

// Called when the game starts or when spawned
void ACloudSpawner::BeginPlay()
{
	Super::BeginPlay();
	ResetCloud();
}

// Called every frame
void ACloudSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACloudSpawner::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	Muffin = Cast<AMuffin>(OtherActor);
	if (Muffin)
	{
		SpawnCloud();
	}
}

