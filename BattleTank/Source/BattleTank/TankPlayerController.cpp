// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATank* 
ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ThisTank = GetControlledTank();
	if (ThisTank)
	{
		UE_LOG(LogTemp, Warning, TEXT(" Possessed Tank is (%s)"), *ThisTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" Tank Player Controller has no Tank associated (%s)"), *GetOwner()->GetName());
	}
}
