// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "BallAimingComponent.h"


// Sets default values for this component's properties
UBallAimingComponent::UBallAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

}

// Track and lock onto target 
void UBallAimingComponent::AimAt(FVector HitLocation, float FireSpeed) 
{
	if (!Ball) { return; }

	FVector FireVelocity;
	FVector StartLocation = Ball->GetSocketLocation(FName("Projectile")); /// Start aiming from the 'projectile' socket on the ball

	bool bHaveAimDirection = UGameplayStatics::SuggestProjectileVelocity(
		this,
		FireVelocity,
		StartLocation,
		HitLocation,
		FireSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimDirection) {
		auto AimDirection = FireVelocity.GetSafeNormal(); /// Get aim direction in unit vectors
		auto Rotation = AimDirection.Rotation(); // Convert to rotation
		Ball->SetRelativeRotation(FRotator(Rotation.Pitch, Rotation.Yaw, 0.f)); /// Rotate ball to match the aim direction
	}

}

void UBallAimingComponent::SetBallReference(UStaticMeshComponent* BallToSet) 
{
	Ball = BallToSet;
}