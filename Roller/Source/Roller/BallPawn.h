// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "BallPawn.generated.h"

UCLASS()
class ROLLER_API ABallPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABallPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Move forward
	void MoveForwardInput(float Val);
	// Move right
	void MoveRightInput(float Val);

private:
	// The mesh component
	class UStaticMeshComponent* BallMeshComponent;

	// The camera
	class UCameraComponent* CameraComponent;

	// Camera boom positioning the camera above the character
	class USpringArmComponent* CameraBoom;

	// Current forward speed
	float CurrentForwardSpeed;

	// Current rotation speed
	float CurrentRotationSpeed;
	
};
