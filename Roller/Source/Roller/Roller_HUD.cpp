// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Roller_HUD.h"

#include "RollerPlayerState.h"

#define LOCTEXT_NAMESPACE "HUD"
ARoller_HUD::ARoller_HUD()
{
	static ConstructorHelpers::FObjectFinder<UFont>Font(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = Font.Object;
}
void ARoller_HUD::DrawHUD()
{
	// Call parent.
	Super::DrawHUD();
	if (CurrentState)
	{
		// Get screen dimensions.
		FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);
		FText LivesString = FText::Format(LOCTEXT("TestFormat", "Score: {0}"),
			FText::AsNumber(CurrentState->GetPlayerScore()));
		FVector2D TextCentrePos = FVector2D((Canvas->SizeX - 200), 10);
		FCanvasTextItem TextItem(TextCentrePos, LivesString, HUDFont, FLinearColor::White);
		Canvas->DrawItem(TextItem);
	}
	else
	{
		// Get the player and player state
		APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		// First, check found the player pawn
		if (Player)
		{
			CurrentState = Cast<ARollerPlayerState>(Player->PlayerState);
		}
	}
}
#undef LOCTEXT_NAMESPACE