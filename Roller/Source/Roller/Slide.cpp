// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Slide.h"

#define OUT

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

	SetInitialPlatformLocation();
	SlidePlatform();

	if (Trigger->GetName().Contains(TEXT("TriggerVolume3"), ESearchCase::IgnoreCase, ESearchDir::FromStart)) {
		SecondTriggeringActor; //TODO assign triggering actor (cube)
	}

	TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	

	if (TriggeringActor == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Triggering actor not found"));
	}
	if (SecondTriggeringActor == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Triggering actor not found"));
	}
	if (Trigger == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s missing trigger "), *(Owner->GetName()));
	}
}

void USlide::SetInitialPlatformLocation()
{
	if (!Owner) { return; }

	Owner->SetActorLocation(Location + FVector(MovementDirection.X, MovementDirection.Y, MovementDirection.Z));

}

void USlide::ResetPosition()
{
	if (!Owner) { return; }

	Owner->SetActorLocation(Location);

}

void USlide::SlidePlatform()
{
	OnSlide.Broadcast();
}

// Called every frame
void USlide::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Trigger) { return; }

	/// If Actor is on Trigger Volume, move platform
	if (Trigger->IsOverlappingActor(TriggeringActor) || Trigger->IsOverlappingActor(SecondTriggeringActor)) {

		ResetPosition();

		if (Trigger->GetName().Contains(TEXT("TriggerVolume3"), ESearchCase::IgnoreCase, ESearchDir::FromStart)) {
			LastTimeSlide = GetWorld()->GetTimeSeconds();
		}
	}

	if (Trigger->GetName().Contains(TEXT("TriggerVolume3"), ESearchCase::IgnoreCase, ESearchDir::FromStart)) {
		if (GetWorld()->GetTimeSeconds() - LastTimeSlide > ResetDelay) {
			SetInitialPlatformLocation();
		}
	}
}
