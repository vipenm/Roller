// Fill out your copyright notice in the Description page of Project Settings.


#include "Roller.h"
#include "AIBallController.h"

void AAIBallController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerBall = GetPlayerBall();
	auto ControlledBall = GetControlledBall();

	if (!PlayerBall) {
		UE_LOG(LogTemp, Warning, TEXT("AI controller cant find player ball"));
	}

	if (!ControlledBall) {
		UE_LOG(LogTemp, Warning, TEXT("AI ball player controller not possessing a ball"));
	}
}

// Called every frame
void AAIBallController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerBall()) {
		GetControlledBall()->AimAt(GetPlayerBall()->GetActorLocation());
	}
}

ATP_RollingBall* AAIBallController::GetControlledBall() const
{
	return Cast<ATP_RollingBall>(GetPawn());
}

ATP_RollingBall* AAIBallController::GetPlayerBall() const 
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) { return nullptr; }

	return Cast<ATP_RollingBall>(PlayerPawn);
}