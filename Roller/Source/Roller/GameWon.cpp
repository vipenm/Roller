// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "GameWon.h"


// Sets default values for this component's properties
UGameWon::UGameWon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGameWon::BeginPlay()
{
	Super::BeginPlay();

	TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (Trigger == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s missing trigger "), *(Owner->GetName()));
	}
	
}


// Called every frame
void UGameWon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Trigger) { return; }

	if (!TriggeringActor) { return; }

	/// If Actor is on Trigger Volume, open Game Won screen
	if (Trigger->IsOverlappingActor(TriggeringActor)) {
		UGameplayStatics::OpenLevel(this, FName("GameWon"));
	}
}
