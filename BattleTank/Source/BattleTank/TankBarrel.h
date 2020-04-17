// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void ElevateBarrel(float RelativeSpeed);

private:
	// Set the maximum elevation of the Barrel
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40.f;

	// Set the minimum elevation of the Barrel
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0.f;

	// How many degrees per second the barrel can move on Y axis
	UPROPERTY(EditAnywhere, Category = Setup)
	float BarrelSpeed = 5.f;
	
};
