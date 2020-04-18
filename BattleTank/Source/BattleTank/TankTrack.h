// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), ClassGroup=(Custom))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
    // Apply force on track throttle, this will cause the tank to turn to the track side.
    UFUNCTION(BlueprintCallable, Category=Input)
    void SetThrottle(float Throttle);

    // Set the maximum driving force that will be applied on the tank which
    // will make it move
    UPROPERTY(EditAnywhere)
    float TrackMaxDrivingForce = 200000.f;
};
