// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent), ClassGroup=(Custom))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void TurnTurret(float RelativeSpeed);
	
private:
	// Speed of the turret turning in degrees per seconds.
	UPROPERTY(EditAnywhere, Category = Setup)
	float TurningSpeed = 5.f;

};
