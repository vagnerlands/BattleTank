// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ATank* 
ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ThisTank = GetControlledTank();
	if (!ThisTank)
	{
		UE_LOG(LogTemp, Error, TEXT(" Tank Player Controller has no Tank associated (%s)"), *GetOwner()->GetName());
	}

	// get the screen dimensions
	GetViewportSize(ViewportWidth, ViewportHeight);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	ATank* ThisTank = GetControlledTank();
	// do nothing if this pawn has nos controlled tank
	if (!ThisTank) { return; }

	// get world location of the line trace
	FVector HitLocation;
	if (GetSightRayHitLocation(ThisTank, HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT(" Hit Location %s"), *HitLocation.ToString());
		GetControlledTank()->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(ATank* Tank, FVector& HitLocation) const
{
	if (!Tank) {  return false; }
	// get the current tank location
	FVector TankLocation = Tank->GetActorLocation();

	// Find the Crosshair position on 2d space
	FVector2D CrosshairPosition = CrosshairScreenLocation();

	// "de-project' the screen position of the crosshair to the world 
	FVector LookAtDirection;
	FindCrosshairDirectionIn3dSpace(CrosshairPosition, LookAtDirection);

	// line-trace along that look direction and see what we hit
	FHitResult HitResult;
	// start location of the ray-trace
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	// Collision parameters - no complex search and also ignore the possessed tank itself
	FCollisionQueryParams CollisionParameters("", false, this);

	// minimal distance, to avoid glitches
	const float MinDistance = 100.f;
	//DrawDebugLine(GetWorld(), StartLocation + (LookAtDirection * MinDistance), (StartLocation + (TankShootRange * LookAtDirection)), FColor::Green, false, -1, 0, 2.f);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, 
		StartLocation + (LookAtDirection * MinDistance),
		StartLocation + (TankShootRange * LookAtDirection),
		ECollisionChannel::ECC_Visibility, 
		CollisionParameters))
	{
		// get the hit location
		HitLocation = HitResult.Location;
		// notify that location was found
		return true;
	}

	// if we got to this point, nothing was hit
	return false;
}


void ATankPlayerController::FindCrosshairDirectionIn3dSpace(FVector2D CrosshairPosition, FVector& LookAtDirection) const
{
	FVector LookLocation;
	DeprojectScreenPositionToWorld(CrosshairPosition.X, CrosshairPosition.Y, LookLocation, LookAtDirection);
	//UE_LOG(LogTemp, Warning, TEXT(" World Location %s   World Direction %s"), *WorldLocation.ToString(), *WorldDirection.ToString());
}