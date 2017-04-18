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

void UBallAimingComponent::AimAt(FVector HitLocation, float FireSpeed) 
{
	if (!Ball) { return; }

	FVector FireVelocity;
	FVector StartLocation = Ball->GetSocketLocation(FName("Projectile"));

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
		auto AimDirection = FireVelocity.GetSafeNormal();
		auto Rotation = AimDirection.Rotation();
		Ball->SetRelativeRotation(FRotator(0.f, Rotation.Yaw, 0.f));
	}

}

void UBallAimingComponent::SetBallReference(UStaticMeshComponent* BallToSet) 
{
	Ball = BallToSet;
}