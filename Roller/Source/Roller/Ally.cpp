// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Ally.h"


// Sets default values
AAlly::AAlly()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAlly::BeginPlay()
{
	Super::BeginPlay();

	// Get the radius. The distance to the target position.
	Radius = FVector::Dist(this->GetActorLocation(), TargetPosition);

	// Default theta.
	Theta = FMath::Acos((this->GetActorLocation().X - TargetPosition.X) / Radius);

	if ((this->GetActorLocation().X - TargetPosition.X) < 0 && (this->GetActorLocation().Y - TargetPosition.Y) < 0)
	{
		// Adjust theta.
		Theta = -Theta;
	}	if ((this->GetActorLocation().X - TargetPosition.X) > 0 && (this->GetActorLocation().Y - TargetPosition.Y) < 0)
	{
		// Adjust theta.
		Theta = -Theta;
	}

}

// Called every frame
void AAlly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TempPosition.X = TargetPosition.X + Radius * FMath::Cos(Theta);
	TempPosition.Y = TargetPosition.Y + Radius * FMath::Sin(Theta);
	TempPosition.Z = this->GetActorLocation().Z;

	Theta += Speed * DeltaTime;

	this->SetActorLocation(TempPosition);
}

