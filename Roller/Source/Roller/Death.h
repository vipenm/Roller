// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Death.generated.h"

class ATP_RollingBall;
class URespawn;
class ABallPlayerController;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ROLLER_API UDeath : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDeath();

	TSubclassOf<class APawn> MyRollingBall;

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetTriggeringActor(APawn* Player);

	APawn* GetTriggeringActor();

	ATP_RollingBall* GetPlayerBall() const;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* Trigger = nullptr;

	/// Actor that can trigger the trigger volume
	AActor* TriggeringActor = nullptr;

	ATP_RollingBall* Ball = nullptr;
	
	URespawn* Spawn = nullptr;

	int32 GetPlayerLives();

	void SetPlayerLives(int32 PlayerLives);

private:

	void PlayerDeath();

	APawn* Player;

	int32 Lives = 3;

};
