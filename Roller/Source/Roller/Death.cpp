// Fill out your copyright notice in the Description page of Project Settings.

#include "Roller.h"
#include "Death.h"

#include "TP_RollingBall.h"
#include "Respawn.h"
#include "BallPlayerController.h"

// Sets default values for this component's properties
UDeath::UDeath()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint>RollingBall(TEXT("Blueprint'/Game/Blueprints/MyRollingBall.MyRollingBall'"));
	if (RollingBall.Object) {
		MyRollingBall = (UClass*)RollingBall.Object->GeneratedClass;
	}
}

// Called when the game starts
void UDeath::BeginPlay()
{
	Super::BeginPlay();

	Spawn = GetOwner()->FindComponentByClass<URespawn>();

	Ball = GetPlayerBall();

	if (Spawn == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Spawn location not found"));	
	}
}

// Called every frame
void UDeath::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Trigger) { return; }

	SetTriggeringActor(GetWorld()->GetFirstPlayerController()->GetPawn());

	TriggeringActor = GetTriggeringActor();

	if (TriggeringActor == nullptr) { return; }

	// If Actor is on Trigger Volume,
	if (Trigger->IsOverlappingActor(TriggeringActor)) {
		PlayerDeath(); // Destroy player
	}
}

ATP_RollingBall* UDeath::GetPlayerBall() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) { return nullptr; }

	return Cast<ATP_RollingBall>(PlayerPawn);
}

void UDeath::PlayerDeath()
{
	if (Ball == nullptr) { return; }

	if (Lives == 0) {
		UGameplayStatics::OpenLevel(this, FName("GameOver"));
	}
	else {
		APlayerController* Controller = GetWorld()->GetFirstPlayerController();
		Controller->UnPossess();
		ATP_RollingBall* NewPlayer = GetWorld()->SpawnActor<ATP_RollingBall>(MyRollingBall, Spawn->GetSpawnLocation(), FRotator(0));
		Controller->Possess(NewPlayer);
		Ball->Destroy();
		Ball = NewPlayer;
		Lives--;
		UE_LOG(LogTemp, Warning, TEXT("Lives left: %i"), Lives);
	}
}

void UDeath::SetTriggeringActor(APawn* TriggeringActor)
{
	Player = TriggeringActor;
}

APawn* UDeath::GetTriggeringActor() 
{
	return Player;
}