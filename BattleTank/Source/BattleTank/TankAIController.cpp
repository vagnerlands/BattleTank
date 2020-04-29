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
	APawn* HumanPlayer = FindPlayer();
	// check if the AI can "see" the player
	if (HumanPlayer)
	{
		// Move toward the player
		MoveToActor(HumanPlayer, AcceptanceRadius);
		// move the turret to the player location
		ThisTank->AimAt(HumanPlayer->GetActorLocation());
		// fire if at location
		ThisTank->Fire();
	}
}

APawn* ATankAIController::FindPlayer() const
{
	APawn* HumanPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (HumanPlayer)
	{
		return HumanPlayer;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" IA (%s) couldn't find Player!"), *GetOwner()->GetName());
	}
	return nullptr;
}
