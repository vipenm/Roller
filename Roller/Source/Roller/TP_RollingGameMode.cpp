// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Roller.h"
#include "TP_RollingGameMode.h"
#include "TP_RollingBall.h"
#include "BallPlayerController.h"

ATP_RollingGameMode::ATP_RollingGameMode()
{
	static ConstructorHelpers::FObjectFinder<UBlueprint>RollingBall(TEXT("Blueprint'/Game/Blueprints/MyRollingBall.MyRollingBall'"));
	if (RollingBall.Object) {
		DefaultPawnClass = (UClass*)RollingBall.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint>BallController(TEXT("Blueprint'/Game/Blueprints/BallPlayerContoller_BP.BallPlayerContoller_BP'"));
	if (BallController.Object) {
		PlayerControllerClass = (UClass*)BallController.Object->GeneratedClass;
	}
}
