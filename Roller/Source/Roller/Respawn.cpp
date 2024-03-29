// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Respawn.h"

#include "TP_RollingBall.h"


/// Sets default values for this component's properties
URespawn::URespawn()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void URespawn::BeginPlay()
{
	Super::BeginPlay();

	TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn(); // Find the triggering actor

	Ball = GetPlayerBall(); // Find the current player

}

// Called every frame
void URespawn::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Trigger) { return; }

	if (!Ball) { return; }

	// If Actor is on checkpoint,
	if (Trigger->IsOverlappingActor(TriggeringActor)) {
		Ball->SetSpawnLocation(GetOwner()->GetActorLocation()); // Set the new spawn location
	}
}

ATP_RollingBall* URespawn::GetPlayerBall() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) { return nullptr; }

	return Cast<ATP_RollingBall>(PlayerPawn);
}
