// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "RollerPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ROLLER_API ARollerPlayerState : public APlayerState
{
	GENERATED_BODY()
	
	int32 PlayerLives;

public:
	ARollerPlayerState();

	void SetPlayerLives(int32 Lives);

	int32 GetPlayerLives();

	// Check if player has reached checkpoint
	bool bCheckpointReached = false;

	// Get time player reached checkpoint
	float LastCheckpointTime;

	// Add delay so message on HUD disappears after 2 seconds
	float CheckpointDelay = 2.0f;

	// Check if item collected
	bool bThrusterCollected = false;
	
};
