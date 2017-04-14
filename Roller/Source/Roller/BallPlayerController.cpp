// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "BallPlayerController.h"

void ABallPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	auto ControlledBall = GetControlledBall();
	if (!ControlledBall) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing ball"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledBall->GetName()));
	}
}

// Called every frame
void ABallPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ABall* ABallPlayerController::GetControlledBall() const 
{
	return Cast<ABall>(GetPawn());
}

