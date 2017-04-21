// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AIBallController.generated.h"

class ATP_RollingBall;

/**
 * 
 */
UCLASS()
class ROLLER_API AAIBallController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	/// Get ball controlled by AI
	ATP_RollingBall* GetControlledBall() const;

	/// Get ball controlled by player
	ATP_RollingBall* GetPlayerBall() const;

	/// Use Pythagoras' Theorem to get distance between AI and Player
	float GetDistanceBetweenAIAndPlayer();

	/// Declare max distance in metres between player and AI that the AI can start firing
	UPROPERTY(EditAnywhere)
	float MaxFiringDistance = 20;

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	bool bCanFire = true;
};