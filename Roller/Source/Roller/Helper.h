// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Helper.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROLLER_API UHelper : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHelper();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	
	UInputComponent* InputComponent = nullptr;

	void Grab();

	void Release();

	void FindPhysicsComponent();

	void SetupInput();

	FVector GetReach();

	FVector GetViewPoint();

	// Return hit for first physics body in reach
	const FHitResult GetPhysicsBody();
};
