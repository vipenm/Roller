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
	
	int PlayerScore;

public:
	ARollerPlayerState();

	void SetPlayerScore(int Score);

	int GetPlayerScore();
	
};
