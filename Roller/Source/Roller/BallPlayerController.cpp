// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "BallPlayerController.h"



ABall* ABallPlayerController::GetControlledBall() const 
{
	return Cast<ABall>(GetPawn());
}


