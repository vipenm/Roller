// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Interactor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROLLER_API UInteractor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	/// Grab object in reach
	void Grabbed();

	/// Release grabbed object
	void Released();

	/// Find and setup physics handle
	void SetupPhysicsHandle();

	/// Find and setup input component
	void SetupInputComponent();

	/// Get the reach of the player
	FVector GetReachEnd();

	/// Get reach start location
	FVector GetReachStart();

	/// Find the first object in reach
	FHitResult GetObjectInReach();

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	/// Define sensible value for the reach of the player
	float Reach = 400.0f;
	
};
