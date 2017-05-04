// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "RollerPlayerState.h"

ARollerPlayerState::ARollerPlayerState()
{
	PlayerLives = 5;
}

void ARollerPlayerState::SetPlayerLives(int32 Lives)
{
	PlayerLives = Lives;
}

int32 ARollerPlayerState::GetPlayerLives()
{
	return PlayerLives ;
}
