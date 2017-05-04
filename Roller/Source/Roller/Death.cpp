// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Death.h"

#include "TP_RollingBall.h"
#include "BallPlayerController.h"
#include "RollerPlayerState.h"

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

	TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn(); // Assign player as the triggering actor

	Comp = Ball->GetRootPrimitiveComponent(); // Get root component of player

	CurrentState = Ball->GetPlayerState(); // Get the player state

}

// Called every frame
void UDeath::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!TriggerA) { return; }
	if (!TriggerB) { return; }
	if (!TriggerC) { return; }
	if (!TriggerD) { return; }
	if (!TriggerE) { return; }
	if (!TriggerF) { return; }
	if (CurrentState == nullptr) { return; }

	if (!TriggeringActor) { return; }

	/// Call to player state to update HUD when a checkpoint is reached
	if (CurrentState->bCheckpointReached) {
		if (GetWorld()->GetTimeSeconds() - CurrentState->LastCheckpointTime > CurrentState->CheckpointDelay) {
			CurrentState->bCheckpointReached = false;
		}
	}

	// If Actor is on Trigger Volume, kill player
	if (TriggerA->IsOverlappingActor(TriggeringActor)) {
		PlayerDeath();
	} 
	else if (TriggerB->IsOverlappingActor(TriggeringActor)) {
		PlayerDeath();
	}
	else if (TriggerC->IsOverlappingActor(TriggeringActor)) {
		PlayerDeath();
	}
	else if (TriggerD->IsOverlappingActor(TriggeringActor)) {
		PlayerDeath();
	}
	else if (TriggerE->IsOverlappingActor(TriggeringActor)) {
		PlayerDeath();
	}
	else if (TriggerF->IsOverlappingActor(TriggeringActor)) {
		PlayerDeath();
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
	if (CurrentState == nullptr) { return; }

	if (CurrentState->GetPlayerLives() == 0) {
		UGameplayStatics::OpenLevel(this, FName("GameOver")); // If player has died too many times, open Game Over screen
	}
	else {
		Comp->SetPhysicsLinearVelocity(FVector(0)); // Set linear velocity to 0 so player doesn't continue falling on spawn
		Comp->SetPhysicsAngularVelocity(FVector(0)); // Set angular velocity to 0 so player doesn't continue rolling on spawn
		Ball->SetActorLocation(Ball->GetSpawnLocation()); // Spawn player at checkpoint
		CurrentState->SetPlayerLives(CurrentState->GetPlayerLives() - 1); // Remove a life
		GetOwner()->GetActorLocation();
	}
}