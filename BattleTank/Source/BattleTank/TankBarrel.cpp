// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	// clamp from -1 to +1, where -1 and +1 is maximum speed on each direction
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	// Elevation change of the Mesh
	float ElevationChange = RelativeSpeed * BarrelSpeed * GetWorld()->DeltaTimeSeconds;
	float NewElevation = RelativeRotation.Pitch + ElevationChange;
	// clamp based on min/max elevation possible
	NewElevation = FMath::Clamp<float>(NewElevation, MinElevationDegrees, MaxElevationDegrees);
	// update the barrel elevation
	SetRelativeRotation(FRotator(NewElevation, 0.f, 0.f));
}