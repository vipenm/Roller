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

	// ...
}


// Called when the game starts
void UTeleport::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	Location = Owner->GetActorLocation();

	TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void UTeleport::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (Trigger->IsOverlappingActor(TriggeringActor)) {
		Location.Z += 75.f;
		TriggeringActor->SetActorLocation(Location);
	}
}

