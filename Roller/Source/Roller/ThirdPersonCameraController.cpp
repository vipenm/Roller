// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "ThirdPersonCameraController.h"


// Sets default values
AThirdPersonCameraController::AThirdPersonCameraController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create camera component.
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	// Set the camera to the root component.
	RootComponent = CameraComponent;
}

// Called when the game starts or when spawned
void AThirdPersonCameraController::BeginPlay()
{
	Super::BeginPlay();
	
	// Set this actor's camera as the current view target.
	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		APlayerController* const PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->SetViewTarget(this);
		}
	}
}

// Called every frame
void AThirdPersonCameraController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

