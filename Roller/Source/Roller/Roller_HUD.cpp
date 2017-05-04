// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Roller_HUD.h"

#include "RollerPlayerState.h"

#define LOCTEXT_NAMESPACE "HUD"
ARoller_HUD::ARoller_HUD()
{
	static ConstructorHelpers::FObjectFinder<UFont>Font(TEXT("Font'/Game/Font/membra.membra'"));
	HUDFont = Font.Object;
	HUDFont->LegacyFontSize = 30;
	
}
void ARoller_HUD::DrawHUD()
{
	// Call parent.
	Super::DrawHUD();

	// Only draw the HUD when main level is loaded
	if (CurrentState && (GetWorld()->GetMapName().Contains(TEXT("Roller"), ESearchCase::IgnoreCase, ESearchDir::FromStart)))
	{
		// Get screen dimensions and display appropriate messages
		FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);
		FText LivesString = FText::Format(LOCTEXT("TestFormat", "Lives: {0}"), FText::AsNumber(CurrentState->GetPlayerLives()));
		FVector2D TextCentrePos = FVector2D((Canvas->SizeX - 250), 20);
		FCanvasTextItem TextItem(TextCentrePos, LivesString, HUDFont, FLinearColor::White);
		Canvas->DrawItem(TextItem);

		if (CurrentState->bCheckpointReached) {
			FString Checkpoint = "Checkpoint\nReached";
			FText CheckpointString = FText::FromString(Checkpoint);
			FVector2D CheckpointTextCentrePos = FVector2D(((Canvas->SizeX - Canvas->SizeX) + 50), 20);
			FCanvasTextItem CheckpointTextItem(CheckpointTextCentrePos, CheckpointString, HUDFont, FLinearColor::White);
			Canvas->DrawItem(CheckpointTextItem);
		}

		if (CurrentState->bThrusterCollected) {
			FString Item = "Space Bar to jump higher";
			FText ItemString = FText::FromString(Item);
			FVector2D ItemTextCentrePos = FVector2D(((Canvas->SizeX / 2) - 350), (Canvas->SizeY - 100));
			FCanvasTextItem ItemTextItem(ItemTextCentrePos, ItemString, HUDFont, FLinearColor::White);
			Canvas->DrawItem(ItemTextItem);
		}
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