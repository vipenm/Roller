// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "BallPlayerController.h"

#include "TP_RollingBall.h"

void ABallPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	auto ControlledBall = GetControlledBall();
	if (!ControlledBall) {
		UE_LOG(LogTemp, Warning, TEXT("Ball player controller not possessing a ball"));
	}
}

// Called every frame
void ABallPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ATP_RollingBall* ABallPlayerController::GetControlledBall() const
{
	return Cast<ATP_RollingBall>(GetPawn());
}
