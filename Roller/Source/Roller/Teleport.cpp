// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Teleport.h"


// Sets default values for this component's properties
UTeleport::UTeleport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UTeleport::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	// Get location of player
	Location = Owner->GetActorLocation();

	// Define player as triggering actor for the trigger volume
	TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (Trigger == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s missing trigger "), *(Owner->GetName()));
	}
	
}

// Called every frame
void UTeleport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Trigger) { return; }

	if (!TriggeringActor) { return; }

	if (Trigger->IsOverlappingActor(TriggeringActor)) { // Check if the player is overlapping the trigger volume
		Location.Z += 75.f;
		TriggeringActor->SetActorLocation(Location); // Teleport player
	}
}
