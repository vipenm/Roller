// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Life.generated.h"

class ARollerPlayerState;
class ATP_RollingBall;

UCLASS()
class ROLLER_API ALife : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALife();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/// Reference to the player
	ATP_RollingBall* Ball = nullptr;

	ATP_RollingBall * GetPlayerBall() const;

	ARollerPlayerState* CurrentState = nullptr;
	
};
