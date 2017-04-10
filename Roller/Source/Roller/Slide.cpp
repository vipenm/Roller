// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Slide.h"

// Sets default values for this component's properties
USlide::USlide()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USlide::BeginPlay()
{
	Super::BeginPlay();

	Location = Owner->GetActorLocation();	
	
}


// Called every frame
void USlide::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//if (Location.X == 1230.f) {
		Owner->SetActorLocation(Location + MovementDirection * DeltaTime);
	/*}
	else if (Location.X == 1630.f) {
		this->GetOwner()->SetActorLocation(Location - MovementDirection * DeltaTime);
	}*/
	
}

