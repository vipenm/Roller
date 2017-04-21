// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Respawn.h"


// Sets default values for this component's properties
URespawn::URespawn()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URespawn::BeginPlay()
{
	Super::BeginPlay();

	TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (TriggeringActor == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Triggering actor not found"));
	}
	
}

// Called every frame
void URespawn::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!Trigger) { return; }

	// If Actor is on Trigger Volume,
	if (Trigger->IsOverlappingActor(TriggeringActor)) {
		SpawnLocation = GetOwner()->GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Spawn Location: %s"), *GetSpawnLocation().ToString());
	}
}

FVector URespawn::GetSpawnLocation() 
{
	return SpawnLocation + FVector(0.f, 0.f, 70.f);
}

void URespawn::SetSpawnLocation(FVector NewLocation) {
	SpawnLocation = NewLocation;
}
