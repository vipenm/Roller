// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "MyStaticMeshComponent.h"

// TODO Lecture 150

UMyStaticMeshComponent::UMyStaticMeshComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

/*void UMyStaticMeshComponent::BeginPlay()
{

}*/

void UMyStaticMeshComponent::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UMyStaticMeshComponent::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

