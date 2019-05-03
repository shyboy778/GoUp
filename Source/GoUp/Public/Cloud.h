// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cloud.generated.h"

class USoundCue;
class UTextRenderComponent;
class AMuffin;
class UBoxComponent;
class UAudioComponent;

UCLASS()
class GOUP_API ACloud : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACloud();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere,Category="Collision")
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * CloudPlane;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * RainPlane;

	UPROPERTY(EditAnyWhere,Category="show")
	TArray<UTexture*> Textures;

	UPROPERTY(BlueprintReadWrite, Category = "show")
	UMaterialInstanceDynamic * MatIstance;
	UMaterialInterface * MatInterface;

	UPROPERTY(VisibleAnyWhere, Category = "show")
	UTextRenderComponent* ScoreText;

	AMuffin* Muffin;

	UPROPERTY(EditAnywhere,Category="sound")
	USoundCue* CloudSound;

	UPROPERTY(VisibleAnywhere,Category="sound")
	UAudioComponent* AudioComp;

	void setRandomCloudTexture();
	void DisplayScore();

	//定义这个函数在蓝图中实现
	UFUNCTION(BlueprintImplementableEvent)
	void FadeOut();

	void EnableRain();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	
	
	
};
