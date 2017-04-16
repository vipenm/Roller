// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Interactor.h"

#define OUT


// Sets default values for this component's properties
UInteractor::UInteractor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractor::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UInteractor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	PlayerViewPointLocation += FVector(300.f, 0.f, -70.f);

	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	FVector ReachEnd = PlayerViewPointLocation + FVector(300.0f, 0.0f, 100.0f);

	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		ReachEnd,
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		10.f
	);
}

