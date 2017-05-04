// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Thruster.generated.h"

class ATP_RollingBall;
class ARollerPlayerState;

UCLASS()
class ROLLER_API AThruster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThruster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// Get the current player
	ATP_RollingBall* GetPlayerBall() const;

private:

	ATP_RollingBall* Ball = nullptr;

	// Set time of when item was collected
	float ItemCollectedTime;

	// Stop item from working 2 seconds after collection
	float ItemWearOffDelay = 2.0f;

	// Check if item is collected
	bool bItemCollected = false;

	ARollerPlayerState* CurrentState = nullptr;
	
};
