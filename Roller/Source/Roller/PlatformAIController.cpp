// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "PlatformAIController.h"

void APlatformAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerBall = GetPlayerBall();
	if (!PlayerBall) {
		UE_LOG(LogTemp, Warning, TEXT("AIController cant find player ball"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *(PlayerBall->GetName()));
	}
}

ABall* APlatformAIController::GetControlledBall() const
{
	return Cast<ABall>(GetPawn());
}

ABall* APlatformAIController::GetPlayerBall() const
{
	auto PlayerBall = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (!PlayerBall) { return nullptr; }

	return Cast<ABall>(PlayerBall);
}

