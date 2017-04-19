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

	// Get approximate distance between AI and player in metres
	void GetDistance();

	// Get AI possessed ball
	ATP_RollingBall* GetControlledBall() const;

	// Get player possessed ball
	ATP_RollingBall* GetPlayerBall() const;

};
