// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "BallPawn.h"

#include "Interaction.h"

//#define OUT

// Sets default values
ABallPawn::ABallPawn()
{

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the mesh component.
	BallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	RootComponent = BallMeshComponent;
	BallMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	// Get the ship mesh.
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		BallMesh(TEXT("StaticMesh'/Game/Mat_Ball.Mat_Ball'"));
	// If the mesh was found set it and set properties.
	if (BallMesh.Succeeded())
	{
		BallMeshComponent->SetStaticMesh(BallMesh.Object);
	}
	
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = false; // We want the arm to rotate when ship does
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->RelativeRotation = FRotator(-30.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
										  // Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	CurrentForwardSpeed = 0.0f;
	CurrentRotationSpeed = 0.0f;
}

// Called when the game starts or when spawned
void ABallPawn::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(7.2f, -4.1f, 70.26f));	
}

// Called every frame
void ABallPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// Move Forward and back.
	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaTime, 0.f, 0.f);
	// Move forwards (with sweep so we stop when we collide with things)
	AddActorLocalOffset(LocalMove, true);
	// Calculate change in rotation this frame
	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Yaw = CurrentRotationSpeed * DeltaTime;
	// Rotate ball
	AddActorLocalRotation(DeltaRotation);
}

// Called to bind functionality to input
void ABallPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// Bind movement to callback functions.
	InputComponent->BindAxis("MoveForward", this, &ABallPawn::MoveForwardInput);
	InputComponent->BindAxis("MoveRight", this, &ABallPawn::MoveRightInput);

}

// Called when a move forward or backward event occurs.
void ABallPawn::MoveForwardInput(float Val)
{
	// Is there no input?
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	if (bHasInput)
	{
		CurrentForwardSpeed = Val * 1000.0f;
	}
	else
	{
		CurrentForwardSpeed = 0;
	}
}

// Called when a rotate left or right event occurs.
void ABallPawn::MoveRightInput(float Val)
{
	// Is there no input?
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	if (bHasInput)
	{
		CurrentRotationSpeed = Val * 250.0f;
	}
	else
	{
		CurrentRotationSpeed = 0;
	}
}
