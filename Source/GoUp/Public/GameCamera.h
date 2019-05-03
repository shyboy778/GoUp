// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameCamera.generated.h"



class UBoxComponent;
class UCameraComponent;
class AMuffin;

UCLASS()
class GOUP_API AGameCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = "components")
	UCameraComponent * CameraComp;

	APlayerController * PlayControl;
	AMuffin * Muffin;

	

	UPROPERTY(VisibleAnywhere,Category="components")
	UBoxComponent* DestoryArea;

	void CameraMove();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UPROPERTY(BlueprintReadWrite)
	bool isFollowPlayer;

	void CheckIfFalling();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTimer();

	UFUNCTION(BlueprintImplementableEvent)
	void ResetTimer();

	//蓝图可以调用的
	UFUNCTION(BlueprintCallable)
	void OnSureFalling();
};
