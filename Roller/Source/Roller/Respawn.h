// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Respawn.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROLLER_API URespawn : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URespawn();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* Trigger = nullptr;

	FVector GetSpawnLocation();

	void SetSpawnLocation(FVector NewLocation);

private:

	/// Actor that can trigger the trigger volume
	AActor* TriggeringActor = nullptr;

	FVector SpawnLocation;
	
};
