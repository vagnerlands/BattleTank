// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
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
		UE_LOG(LogTemp, Error, TEXT(" AI Tank has possessed NO Tank (%s)"), *GetOwner()->GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}