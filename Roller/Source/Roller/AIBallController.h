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

	/// Create state machine
	enum class EFiringStatus
	{
		Scan,
		Lock_On,
		Fire,
		Stop
	};

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	/// Get ball controlled by AI
	ATP_RollingBall* GetControlledBall() const;

	/// Get ball controlled by player
	ATP_RollingBall* GetPlayerBall() const;

	/// Use Pythagoras' Theorem to get distance between AI and Player
	float GetDistanceBetweenAIAndPlayer();

	/// Setup state machine
	EFiringStatus CheckFiringState(float Distance);

	/// Make AI rotate randomly searching for player
	void Scan();

	bool Stop();

private:
	/// Declare max distance in metres between player and AI that the AI can start firing
	float MaxFiringDistance = 25;

	/// Declare 'out of range' distance where the AI should scan for player
	float MaxScanningDistance = 40;

	/// Minimum rotation range of AI
	float MinRotationRange = -30.0f;

	/// Maximum rotation range of AI
	float MaxRotationRange = 30.0f;

	/// Make AI stop after reaching certain point
	bool bStopAI = true;

};
