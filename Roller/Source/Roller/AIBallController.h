// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TP_RollingBall.h"

#include "AIController.h"
#include "AIBallController.generated.h"

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

};
