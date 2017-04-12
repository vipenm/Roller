// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Slide.h"

// Sets default values for this component's properties
USlide::USlide()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void USlide::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	if (!Owner) { return; }

	Location = Owner->GetActorLocation();	
	
	SlidePlatform();

	TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (TriggeringActor == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Triggering actor not found"));
	}
	if (Trigger == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s missing trigger "), *(Owner->GetName()));
	}
	
}

void USlide::SlidePlatform()
{
	//if (!Owner) { return; }

	//Owner->SetActorLocation(Location + FVector(MovementDirection.X, MovementDirection.Y, MovementDirection.Z));

	OnSlide.Broadcast();
}

void USlide::ResetPosition()
{
	if (!Owner) { return; }
	
	Owner->SetActorLocation(Location);
}


// Called every frame
void USlide::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );	
	if (!Trigger) {	return; }
	/// If Actor is on Trigger Volume, move platform
	if (Trigger->IsOverlappingActor(TriggeringActor)) {
		ResetPosition();
	}
}
