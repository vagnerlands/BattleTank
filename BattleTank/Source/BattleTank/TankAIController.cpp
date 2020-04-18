// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Tank Pawn reference
	ATank* ThisTank = Cast<ATank>(GetPawn());
	// player location placeholder 
	FVector PlayerLocation;
	// check if the AI can "see" the player
	if (DetectPlayer(PlayerLocation))
	{
		// move the turret to the player location
		ThisTank->AimAt(PlayerLocation);
		// fire if at location
		ThisTank->Fire();
	}
}

bool ATankAIController::DetectPlayer(FVector& PlayerLocation) const
{
	APawn* GamePlayer = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (GamePlayer)
	{
		//UE_LOG(LogTemp, Warning, TEXT(" IA (%s) found Player at (%s)"), *GetControlledTank()->GetName(), *GamePlayer->GetName());
		PlayerLocation = GamePlayer->GetActorLocation();
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" IA (%s) couldn't find Player!"), *GetOwner()->GetName());
	}
	return false;
}
