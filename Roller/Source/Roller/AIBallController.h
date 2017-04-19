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

	ATP_RollingBall* GetControlledBall() const;

	ATP_RollingBall* GetPlayerBall() const;

	// Use Pythagoras' Theorem to get distance between AI and Player
	void GetDistanceBetweenAIAndPlayer();
};
