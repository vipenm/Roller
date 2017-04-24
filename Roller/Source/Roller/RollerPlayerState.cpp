// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "RollerPlayerState.h"

ARollerPlayerState::ARollerPlayerState()
{
	PlayerScore = 0;
}

void ARollerPlayerState::SetPlayerScore(int Score)
{
	PlayerScore = Score;
}

int ARollerPlayerState::GetPlayerScore()
{
	return PlayerScore;
}
