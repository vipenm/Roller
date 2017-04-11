// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Helper.h"

#define OUT


// Sets default values for this component's properties
UHelper::UHelper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHelper::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHelper::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/// Get player viewpoint
	FVector PlayerViewPoint;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPoint,
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPoint + PlayerViewPointRotation.Vector() * Reach;
	DrawDebugLine(
		GetWorld(),
		PlayerViewPoint,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
		);

}
