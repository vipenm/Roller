// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Slide.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlide);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlide);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROLLER_API USlide : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlide();

	// Called when the game starts
	virtual void BeginPlay() override;

	void SetInitialPlatformLocation();
	void ResetPosition();
	void SlidePlatform();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	/*UPROPERTY(BlueprintAssignable)
		FOnSlide OnSlide;*/

	UPROPERTY(BlueprintAssignable)
		FOnSlide OnSlide;

private:
	
	AActor* Owner = nullptr;
	FVector Location;
	
	UPROPERTY(EditAnywhere)
	FVector MovementDirection;
	
	UPROPERTY(EditAnywhere)
		ATriggerVolume* Trigger = nullptr;

	AActor* TriggeringActor = nullptr;
};
