// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Muffin.generated.h"

UCLASS()
class GOUP_API AMuffin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMuffin();

	void MoveToCursor();

	UFUNCTION(BlueprintImplementableEvent)
	void MoveToTouch();

	void LaunchStart();

	void SetSpeed();

	void GameOver();

	UFUNCTION(BlueprintCallable)
	void ResetGame();

	//œ‘ æ÷ÿ∆Ù∞¥≈•
	UFUNCTION(BlueprintImplementableEvent)
	void ShowRestart();

	UPROPERTY(EditAnywhere, Category = "speed")
	float AirSpeed;
	UPROPERTY(EditAnywhere, Category = "speed")
	float GroundSpeed;
	
	UPROPERTY(BlueprintReadOnly)
	bool isDeath;
	bool isGameStarted;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	APlayerController * PlayControl;
	FVector LaunchVelocity;

	int Score;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Launch();
	void IncreaseScore();
	int GetScore() const;
};
