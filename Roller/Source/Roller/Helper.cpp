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
	FindInputComponent();
	
}

/// Find physics handle component
void UHelper::FindPhysicsComponent() {

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		// Physics handle found
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s Physics handle not found"), *GetOwner()->GetName());
	}
}

/// Find and setup input component
void UHelper::FindInputComponent() {
	
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Input component found"));
		/// Bind input controls
		InputComponent->BindAction("Grab", IE_Pressed, this, &UHelper::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UHelper::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s Input component not found"), *GetOwner()->GetName());
	}
}

void UHelper::Grab() 
{
	/// Try and reach any actors with physics body collision channel set
	auto HitResult = GetPhysicsBodyInReach();
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

void UHelper::Release()
{
	PhysicsHandle->ReleaseComponent();
}

const FHitResult UHelper::GetPhysicsBodyInReach()
{
	/// Get player viewpoint
	FVector PlayerViewPoint;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPoint,
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPoint + PlayerViewPointRotation.Vector() * Reach;

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace reach distance
	FHitResult LineTraceHit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,
		PlayerViewPoint,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor* ActorHit = LineTraceHit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
	}

	return LineTraceHit;
}

// Called every frame
void UHelper::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	FVector PlayerViewPoint;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPoint,
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPoint + PlayerViewPointRotation.Vector() * Reach;

	// If the physics handle is attached
	if (PhysicsHandle->GrabbedComponent) {
		// move the object were holding
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
		

}
