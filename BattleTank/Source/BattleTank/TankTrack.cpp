// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
//	UE_LOG(LogTemp, Warning, TEXT(" %s was set to %f "), *GetOwner()->GetName(), Throttle);

	FVector ForceApplied = GetForwardVector() * Throttle* TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(  GetOwner()->GetRootComponent() );
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}