// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "BallPlayerController.generated.h"


class ATP_RollingBall;
/**
 * 
 */
UCLASS()
class ROLLER_API ABallPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	/// Get the ball controlled by the player
	ATP_RollingBall* GetControlledBall() const;
};
