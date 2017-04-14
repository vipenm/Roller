// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Ball.h"


// Sets default values
ABall::ABall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ABall::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ABall::SetSpeed(float Speed) {
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%f Speed of %s"), Speed, *Name);

	// TODO clamp speed so player can't override
}