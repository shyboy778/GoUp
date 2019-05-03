// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CloudSpawner.generated.h"

class ACloud;
class UBoxComponent;
class AMuffin;
UCLASS()
class GOUP_API ACloudSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACloudSpawner();
	void SpawnCloud();

	UFUNCTION(BlueprintCallable)
	void ResetCloud();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AMuffin* Muffin;

	UPROPERTY(EditAnywhere,Category="Cloud")
	int InitialSpawnAmount;

	UPROPERTY(EditAnywhere, Category = "Cloud")
	float SpawnSpacing;

	UPROPERTY(VisibleAnywhere,Category="component")
	UBoxComponent * SpawnArea;

	UPROPERTY(VisibleAnywhere, Category = "component")
	UBoxComponent * TriggerArea;

	UPROPERTY(VisibleAnywhere, Category = "component")
	USceneComponent* DefaultRoot;

	UPROPERTY(EditAnyWhere,Category="Cloud")
	//限制赋值类型
	TSubclassOf<ACloud> Cloud;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	
};
