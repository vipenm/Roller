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

	/// Find Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		// Physics handle found
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s Physics handle not found"), *GetOwner()->GetName());
	}

	/// Find Input Component
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
	UE_LOG(LogTemp, Warning, TEXT("Grab Key Pressed"));
}

void UHelper::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Key Released"));
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

}
