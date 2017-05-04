// Fill out your copyright notice in the Description page of Project Settings.


#include "Roller.h"
#include "AIBallController.h"

#include "TP_RollingBall.h"

void AAIBallController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerBall = GetPlayerBall(); // The player
	auto ControlledBall = GetControlledBall(); // The AI

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

		EFiringStatus Status = CheckFiringState(GetDistanceBetweenAIAndPlayer()); // Call State machine

		switch (Status)
		{
		case EFiringStatus::Scan: // If in scanning range, scan
			Scan();
			break;
		case EFiringStatus::Lock_On:
			GetControlledBall()->AimAt(GetPlayerBall()->GetActorLocation()); // Lock on when closer
			break;
		case EFiringStatus::Fire:
			GetControlledBall()->AimAt(GetPlayerBall()->GetActorLocation()); // Fire at player when in range
			GetControlledBall()->Fire();
			break;
		case EFiringStatus::Stop: // Stop after passing the AI
			Stop();
			break;
		default:
			break;
		}
	}
}

// Get the AI ball
ATP_RollingBall* AAIBallController::GetControlledBall() const
{
	return Cast<ATP_RollingBall>(GetPawn());
}

// Get the Player ball
ATP_RollingBall* AAIBallController::GetPlayerBall() const 
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) { return nullptr; }

	return Cast<ATP_RollingBall>(PlayerPawn);
}

float AAIBallController::GetDistanceBetweenAIAndPlayer()
{
	auto PlayerBallLocation = GetPlayerBall()->GetActorLocation();
	auto ControlledBallLocation = GetControlledBall()->GetActorLocation();

	// Get the distance between AI and player in metres using Pythagoras' Theorem
	float Distance = FMath::Sqrt(FMath::Pow((PlayerBallLocation.X - ControlledBallLocation.X), 2) +
		FMath::Pow((PlayerBallLocation.Y - ControlledBallLocation.Y), 2) +
		FMath::Pow((PlayerBallLocation.Z - ControlledBallLocation.Z), 2)) / 100; // Divide by 100 to get metres
	return Distance;
};

AAIBallController::EFiringStatus AAIBallController::CheckFiringState(float Distance)
{
	if (Stop()) {
		return EFiringStatus::Stop; // Stop after passing AI
	}
	// If player is 50 or more metres away
	else if (Distance >= MaxScanningDistance) {
		return EFiringStatus::Scan; 
	}
	// if player is less than 40 but more than 25
	else if (Distance < MaxScanningDistance && Distance > MaxFiringDistance) {
		return EFiringStatus::Lock_On;
	}
	else {
		return EFiringStatus::Fire; // Fire when close enough
	}
}

void AAIBallController::Scan() 
{
	float RandomRotation = FMath::RandRange(MinRotationRange, MaxRotationRange); // Create random float
	GetControlledBall()->SetActorRotation(GetControlledBall()->GetActorRotation() + FRotator(0.f, RandomRotation, 0.f)); // Rotate AI randomly
}

bool AAIBallController::Stop()
{
	auto PlayerBallLocation = GetPlayerBall()->GetActorLocation();
	auto ControlledBallLocation = GetControlledBall()->GetActorLocation();

	if (PlayerBallLocation.Y > ControlledBallLocation.Y) {
		bStopAI = true;
	}
	else {
		bStopAI = false;
	}
	return bStopAI;
}
