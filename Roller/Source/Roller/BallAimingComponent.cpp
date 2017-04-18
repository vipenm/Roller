// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "BallAimingComponent.h"


// Sets default values for this component's properties
UBallAimingComponent::UBallAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBallAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBallAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UBallAimingComponent::AimAt(FVector HitLocation, float FireSpeed) 
{
	if (!Ball) { return; }

	FVector FireVelocity;
	FVector StartLocation = Ball->GetComponentLocation();

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		FireVelocity,
		StartLocation,
		HitLocation,
		FireSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	)) 
	{
		auto AimDirection = FireVelocity.GetSafeNormal();
		auto BallName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s"), *BallName, *AimDirection.ToString());
	}


}

void UBallAimingComponent::SetBallReference(UStaticMeshComponent* BallToSet) 
{
	Ball = BallToSet;
}

