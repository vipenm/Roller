// Fill out your copyright notice in the Description page of Project Settings.


#include "Roller.h"
#include "AIBallController.h"

void AAIBallController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledBall = GetControlledBall();
	if (!ControlledBall) {
		UE_LOG(LogTemp, Warning, TEXT("AI ball player controller not possessing a ball"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI ball player controller possessing: %s"), *GetControlledBall()->GetName());
	}
}

// Called every frame
void AAIBallController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ATP_RollingBall* AAIBallController::GetControlledBall() const
{
	return Cast<ATP_RollingBall>(GetPawn());
}