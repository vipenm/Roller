// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Ally.generated.h"

UCLASS()
class ROLLER_API AAlly : public AActor
{
	GENERATED_BODY()

	// Target position of the actor. The actor will circle around this position.
	UPROPERTY(EditAnywhere)
	FVector TargetPosition;

	UPROPERTY(EditAnywhere)
	float Speed;
	
public:	
	// Sets default values for this actor's properties
	AAlly();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Temp Position for the actor. Used to generate a new position on the circle.
	FVector TempPosition;

	// Radius. Generated from the actor’s current distance to the target.
	float Radius;

	// The current angle in the circle strafe.
	float Theta;
	
};
