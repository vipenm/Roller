// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/Pawn.h"
#include "TP_RollingBall.generated.h"

class UBallAimingComponent;
class AProjectile;

UCLASS(config=Game)
class ATP_RollingBall : public APawn
{
	GENERATED_BODY()

	/** StaticMesh used for the ball */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ball, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Ball;

public:
	ATP_RollingBall();

	void AimAt(FVector HitLocation);

	/** Vertical impulse to apply when pressing jump */
	UPROPERTY(EditAnywhere, Category=Ball)
	float JumpImpulse;

	/** Torque to apply when trying to roll ball */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Ball)
	float RollTorque;

	/** Indicates whether we can currently jump, use to prevent double jumping */
	bool bCanJump;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Called to move ball forwards and backwards */
	void MoveForward(float Val);

	/** Handle jump action. */
	void Jump();

	// AActor interface
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UBallAimingComponent* BallAimingComponent = nullptr;


public:
	/** Returns Ball subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBall() const { return Ball; }

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category= Setup)
	void SetBallReference(UStaticMeshComponent* BallToSet);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();


private:
	UPROPERTY(EditAnywhere, Category = Firing)
	float FireSpeed = 4000;

	UPROPERTY(EditAnywhere, Category = Setup)
	UClass* ProjectileBlueprint;

};
