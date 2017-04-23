// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Death.h"

#include "TP_RollingBall.h"
#include "BallPlayerController.h"
#include "Interactor.h"

// Sets default values for this component's properties
UDeath::UDeath()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UDeath::BeginPlay()
{
	Super::BeginPlay();

	Ball = GetPlayerBall(); // Get the current player

	TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	Comp = Ball->GetRootPrimitiveComponent();
}

// Called every frame
void UDeath::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Trigger) { return; }

	if (!TriggeringActor) { return; }

	// If Actor is on Trigger Volume,
	if (Trigger->IsOverlappingActor(TriggeringActor)) {
		PlayerDeath(); // Destroy player
	}
}

ATP_RollingBall* UDeath::GetPlayerBall() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) { return nullptr; }

	return Cast<ATP_RollingBall>(PlayerPawn);
}

void UDeath::PlayerDeath()
{
	if (Ball == nullptr) { return; }

	if (Lives == 0) {
		UGameplayStatics::OpenLevel(this, FName("GameOver")); // If player has died too many times, open Game Over screen
	}
	else {
		Comp->SetPhysicsLinearVelocity(FVector(0));
		Comp->SetPhysicsAngularVelocity(FVector(0));
		Ball->SetActorLocation(Ball->GetSpawnLocation()); // Spawn player at checkpoint
		Lives--; // Remove a life
	}
}