// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Roller.h"
#include "TP_RollingBall.h"

#include "BallAimingComponent.h"
#include "Projectile.h"

#define OUT

ATP_RollingBall::ATP_RollingBall()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("StaticMesh'/Game/Materials/BallMesh2.BallMesh2'"));

	// Create mesh component for the ball
	Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball0"));
	Ball->SetStaticMesh(BallMesh.Object);
	Ball->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	Ball->SetSimulatePhysics(true);
	Ball->SetAngularDamping(0.1f);
	Ball->SetLinearDamping(0.1f);
	Ball->BodyInstance.MassScale = 3.5f;
	Ball->BodyInstance.MaxAngularVelocity = 800.0f;
	Ball->SetNotifyRigidBodyCollision(true);
	RootComponent = Ball;

	BallAimingComponent = CreateDefaultSubobject<UBallAimingComponent>(FName("Aiming Component"));

	// Set up forces
	RollTorque = 4000000.0f;
	JumpImpulse = 70000.0f;
	bCanJump = true; // Start being able to jump
}

// Called every frame
void ATP_RollingBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATP_RollingBall::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAxis("MoveRight", this, &ATP_RollingBall::MoveRight);
	InputComponent->BindAxis("MoveForward", this, &ATP_RollingBall::MoveForward);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ATP_RollingBall::Jump);
}

void ATP_RollingBall::MoveRight(float Val)
{
	const FVector Torque = FVector(-1.f * Val * RollTorque, 0.f, 0.f);
	Ball->AddTorque(Torque);
	
}

void ATP_RollingBall::MoveForward(float Val)
{
	const FVector Torque = FVector(0.f, Val * RollTorque, 0.f);
	Ball->AddTorque(Torque);
}

void ATP_RollingBall::Jump()
{
	if(bCanJump)
	{
		const FVector Impulse = FVector(0.f, 0.f, JumpImpulse);
		Ball->AddImpulse(Impulse);
		bCanJump = false;
	}
}

void ATP_RollingBall::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	bCanJump = true;
}

void ATP_RollingBall::AimAt(FVector HitLocation) 
{
	BallAimingComponent->AimAt(HitLocation, FireSpeed);
}

void ATP_RollingBall::SetBallReference(UStaticMeshComponent* BallToSet) 
{
	BallAimingComponent->SetBallReference(BallToSet);
	Ball = BallToSet;
}

void ATP_RollingBall::Fire() 
{
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTime; // Check if player can fire again

	if (Ball && bIsReloaded) { // If player can fire again
		auto Projectile = GetWorld()->SpawnActor<AProjectile>( // Spawn projectile
			ProjectileBlueprint,
			Ball->GetSocketLocation(FName("Projectile")), // From 'projectile' socket
			Ball->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(FireSpeed); // Fire
		LastFireTime = GetWorld()->GetTimeSeconds(); // Reset LastFireTime
	}	
}
