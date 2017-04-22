// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Slide.generated.h"

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

	/// Choose starting location of platform
	void SetInitialPlatformLocation();

	/// Set the location of platform to its correct place (location where player can move onto it)
	void ResetPosition();

	/// Slide platform from one location to another continuously
	void SlidePlatform();
	
	/// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	/// Blueprint assignable property so animation of sliding platform can be defined in editor
	UPROPERTY(BlueprintAssignable)
		FOnSlide OnSlide;

private:
	
	AActor* Owner = nullptr;

	/// Default location of platform
	FVector Location;
	
	/// Used in conjunction with SetInitialPlatformLocation() to set offset of platform location
	UPROPERTY(EditAnywhere)
	FVector MovementDirection;
	
	/// Trigger volume
	UPROPERTY(EditAnywhere)
	ATriggerVolume* Trigger = nullptr;

	/// Actor that can trigger the trigger volume
	AActor* TriggeringActor = nullptr;
};
