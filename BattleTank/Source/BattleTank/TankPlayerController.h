// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(ATank* Tank, FVector& HitLocation) const;
	void FindCrosshairDirectionIn3dSpace(FVector2D CrosshairPosition, FVector& LookAtDirection) const;

	FORCEINLINE FVector2D CrosshairScreenLocation() const
	{
		return FVector2D(GetCrosshairRelativeX(), GetCrosshairRelativeY());
	}

	FORCEINLINE float GetCrosshairRelativeX() const
	{
		return CrosshairRelativeX * ViewportWidth;
	}

	FORCEINLINE float GetCrosshairRelativeY() const
	{
		return CrosshairRelativeY * ViewportHeight;
	}

	// screen size dimensions (X and Y)
	int32 ViewportWidth;
	int32 ViewportHeight;

	// relative position of the crosshair on X axis
	UPROPERTY(EditAnywhere)
	float CrosshairRelativeX = .5f;
	// relative position of the crosshair on Y axis
	UPROPERTY(EditAnywhere)
	float CrosshairRelativeY = .33334f;
	// How far the tank can shoot, for ray-tracing calculation
	UPROPERTY(EditAnywhere)
	float TankShootRange = 1000000.f;
};
