// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "Roller_HUD.generated.h"

/**
 * 
 */
UCLASS()
class ROLLER_API ARoller_HUD : public AHUD
{
	GENERATED_BODY()

	class ARollerPlayerState* CurrentState;

public:
	ARoller_HUD();

	// Font used to render info
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;};