// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ThisTank = GetControlledTank();

	if (ThisTank)
	{
		UE_LOG(LogTemp, Warning, TEXT(" AI Tank possessed (%s)"), *ThisTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" AI Tank has possessed NO Tank"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// player location placeholder 
	FVector PlayerLocation;
	// check if the AI can "see" the player
	if (DetectPlayer(PlayerLocation))
	{
		// move the turret to the player location
		GetControlledTank()->AimAt(PlayerLocation);
		// fire if at location
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

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}