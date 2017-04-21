// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Death.h"

#include "TP_RollingBall.h"
#include "Respawn.h"

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

	Ball = GetPlayerBall();

	Spawn = GetOwner()->FindComponentByClass<URespawn>();

	//Spawn = GetRespawn();

	/// Define the player as the triggering actor
	TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (Spawn == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Spawn is null"));
	}
	if (TriggeringActor == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Triggering actor not found"));
	}
}

// Called every frame
void UDeath::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!Trigger) { return; }

	// If Actor is on Trigger Volume,
	if (Trigger->IsOverlappingActor(TriggeringActor)) {
		PlayerDeath(); // Open Game Over Screen
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
	if (Spawn == nullptr) { return; }
	
	auto Lives = Ball->GetPlayerLives();
	if (Lives == 0) {
		UGameplayStatics::OpenLevel(this, FName("GameOver"));
	}
	else {
		Ball->SetPlayerLives(Lives--);
		Ball->Destroy();
		ATP_RollingBall* NewBall = GetWorld()->SpawnActor<ATP_RollingBall>(Spawn->GetSpawnLocation(), FRotator(0));
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Lives left: %f"), Lives);
}

