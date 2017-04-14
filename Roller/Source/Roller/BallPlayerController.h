// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ball.h"

#include "GameFramework/PlayerController.h"
#include "BallPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROLLER_API ABallPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABall* GetControlledBall() const;
	
	
};
