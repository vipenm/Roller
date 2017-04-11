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
}

// Called when the game starts
void UHelper::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsComponent();
	SetupInput();
	
}

// Called every frame
void UHelper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached
	if (PhysicsHandle->GrabbedComponent) {
		// move the object were holding
		PhysicsHandle->SetTargetLocation(GetReach());
	}
}

/// Find physics handle component
void UHelper::FindPhysicsComponent() {

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("%s Physics handle not found"), *GetOwner()->GetName());
	}
}

/// Setup input
void UHelper::SetupInput() {
	
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		/// Bind input controls
		InputComponent->BindAction("Grab", IE_Pressed, this, &UHelper::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UHelper::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s Input component not found"), *GetOwner()->GetName());
	}
}

/// Grab the object
void UHelper::Grab() 
{
	/// Try and reach any actors with physics body collision channel set
	auto HitResult = GetPhysicsBody();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();


	// If we hit something
	if (ActorHit) {
		// Attach physics handle
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
		);
	}
}

/// Release the object
void UHelper::Release()
{
	PhysicsHandle->ReleaseComponent();
}

/// Get the object with a physics body within reach
const FHitResult UHelper::GetPhysicsBody()
{
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace reach distance
	FHitResult LineTraceHit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,
		GetViewPoint(),
		GetReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return LineTraceHit;
}

/// Get the viewpoint of the player
FVector UHelper::GetViewPoint()
{
	FVector PlayerViewPoint;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPoint,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPoint;
}

/// Get the reach of the player
FVector UHelper::GetReach()
{
	FVector PlayerViewPoint;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPoint,
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPoint + PlayerViewPointRotation.Vector() * Reach;

	return LineTraceEnd;
}
