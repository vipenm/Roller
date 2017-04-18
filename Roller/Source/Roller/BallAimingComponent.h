// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "BallAimingComponent.generated.h"

class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROLLER_API UBallAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBallAimingComponent();

	void SetBallReference(UStaticMeshComponent* BallToSet);

	void AimAt(FVector HitLocation, float FireSpeed);

private:
	UStaticMeshComponent* Ball = nullptr;
	
};
