// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Life.h"

#include "RollerPlayerState.h"
#include "TP_RollingBall.h"


// Sets default values
ALife::ALife()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALife::BeginPlay()
{
	Super::BeginPlay();

	Ball = GetPlayerBall(); // Get the current player

	if (Ball == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Ball not found"));
	}

	CurrentState = Ball->GetPlayerState();
	
}

// Called every frame
void ALife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Ball == nullptr) { return; }
	if (CurrentState == nullptr) { return; }

	// Continuosuly rotate life item
	this->SetActorRotation(this->GetActorRotation() + FRotator(0.f, 1.0f, 0.f));

	if (this->IsOverlappingActor(Ball)) {
		CurrentState->SetPlayerLives(CurrentState->GetPlayerLives() + 1); // Add a life when collected
		this->Destroy();
	}

}

ATP_RollingBall* ALife::GetPlayerBall() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) { return nullptr; }

	return Cast<ATP_RollingBall>(PlayerPawn);
}

