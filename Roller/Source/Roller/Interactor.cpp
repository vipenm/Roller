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

}

// Called when the game starts
void UInteractor::BeginPlay()
{
	Super::BeginPlay();	

	SetupPhysicsHandle();
	SetupInputComponent();
	
}

// Called every frame
void UInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Check if anything grabbable in reach
	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(GetReachEnd()); // If so, attach to end of reach of player
	}
}

/// Get the starting point of the reach ie the origin of the player
FVector UInteractor::GetReachStart() 
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	PlayerViewPointLocation += (FVector(0.f, 0.f, -70.f));

	return PlayerViewPointLocation; // return start of reach

}

/// Get the end point of the reach
FVector UInteractor::GetReachEnd() 
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	PlayerViewPointLocation += (FVector(0.f, 0.f, -70.f));

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

	return LineTraceEnd; // return end of reach
}

void UInteractor::SetupPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>(); // find physics handle component

	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle"), *GetOwner()->GetName());
	}
}

void UInteractor::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>(); // find input component

	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UInteractor::Grabbed);
		InputComponent->BindAction("Grab", IE_Released, this, &UInteractor::Released);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName());
	}
}


void UInteractor::Grabbed() 
{
	auto HitResult = GetObjectInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (ActorHit) { // If a suitable object is grabbed 
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
		);
	}
}

void UInteractor::Released()
{
	PhysicsHandle->ReleaseComponent();
}

FHitResult UInteractor::GetObjectInReach()
{
	// line trace to reach distance
	FHitResult LineTraceHit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Ray-cast to get data of object hit depending on player view point and reach
	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,
		GetReachStart(),
		GetReachEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), // Check if object hit has PhysicsBody attribute
		TraceParameters
	);

	return LineTraceHit; // return data of object hit
}
