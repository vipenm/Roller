// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Thruster.h"

#include "TP_RollingBall.h"
#include "RollerPlayerState.h"

// Sets default values
AThruster::AThruster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThruster::BeginPlay()
{
	Super::BeginPlay();

	// Find player
	Ball = GetPlayerBall();

	if (Ball == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Ball not found"));
	}	

	CurrentState = Ball->GetPlayerState();
}

// Called every frame
void AThruster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentState == nullptr) { return; }

	// Continuously rotate item
	this->SetActorRotation(this->GetActorRotation() + FRotator(0.f, 2.0f, 0.f));

	// Check if overlaps with player
	if (this->IsOverlappingActor(Ball)) {
		CurrentState->bThrusterCollected = true; // Tell player state that item has been collected
		ItemCollectedTime = GetWorld()->GetTimeSeconds(); // Set time collected
		this->SetActorHiddenInGame(true); // Temporarily hide item
		this->SetActorLocation(this->GetActorLocation() + (FVector(0.f, 0.f, -200.0f))); // And move so player can no longer collect
		Ball->SetJumpImpulse(140000.0f); // Increase jump height
		bItemCollected = true; 
	}

	if (bItemCollected) {
		/// Called after 2 seconds
		if ((GetWorld()->GetTimeSeconds() - ItemCollectedTime) > ItemWearOffDelay) {
			Ball->SetJumpImpulse(70000.0f); // Reset jump height to normal
			bItemCollected = false;
			CurrentState->bThrusterCollected = false;
			this->Destroy(); // Destroy actor after everything complete
		}
	}
}

ATP_RollingBall* AThruster::GetPlayerBall() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) { return nullptr; }

	return Cast<ATP_RollingBall>(PlayerPawn);
}
