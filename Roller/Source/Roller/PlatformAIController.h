// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ball.h"

#include "AIController.h"
#include "PlatformAIController.generated.h"

/**
 * 
 */
UCLASS()
class ROLLER_API APlatformAIController : public AAIController
{
	GENERATED_BODY()

private:
	ABall* GetControlledBall() const;

	virtual void BeginPlay() override;
	
	ABall* GetPlayerBall() const;
	
};
