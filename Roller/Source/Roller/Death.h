// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Death.generated.h"

class ATP_RollingBall;
class ABallPlayerController;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ROLLER_API UDeath : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDeath();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// Get the current player
	ATP_RollingBall* GetPlayerBall() const;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* Trigger = nullptr;

	/// Actor that can trigger the trigger volume
	AActor* TriggeringActor = nullptr;

	/// Reference to the player
	ATP_RollingBall* Ball = nullptr;	

private:

	/// Kill player
	void PlayerDeath();

	/// Set lives of the player
	int32 Lives = 3;

	UPrimitiveComponent* Comp;

};
