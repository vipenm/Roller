// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Death.h"


// Sets default values for this component's properties
UDeath::UDeath()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDeath::BeginPlay()
{
	Super::BeginPlay();

	/// Define the player as the triggering actor
	TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (TriggeringActor == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Triggering actor not found"));
	}
}


// Called every frame
void UDeath::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!Trigger) { return; }

	/// If Actor is on Trigger Volume, move platform to default location
	if (Trigger->IsOverlappingActor(TriggeringActor)) {
		UGameplayStatics::OpenLevel(this, FName("GameOver"));
	}
}

