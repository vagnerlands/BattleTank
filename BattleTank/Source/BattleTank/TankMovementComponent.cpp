// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void 
UTankMovementComponent::IntendMoveForward(float Throw)
{
	// check for nullptrs
	if ((!LeftTrack) || (!RightTrack)) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void 
UTankMovementComponent::IntendTurnRight(float Throw)
{
	// check for nullptrs
	if ((!LeftTrack) || (!RightTrack)) { return; }

	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

void
UTankMovementComponent::Initialize(UTankTrack* LeftTrackRef, UTankTrack* RightTrackRef)
{
	LeftTrack = LeftTrackRef;
	RightTrack = RightTrackRef;
}


// overriden method from Nav
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector TankRightVector = GetOwner()->GetActorRightVector().GetSafeNormal();
	FVector Movement = MoveVelocity.GetSafeNormal();

	float ForwardIntend = FVector::DotProduct(Movement, TankForwardVector);
	IntendMoveForward(ForwardIntend);

	float TurnIntend = FVector::CrossProduct(Movement, TankForwardVector).Z;
	IntendTurnRight(TurnIntend);

	// Alternative solution, 
	//float TurnIntend = FVector::DotProduct(Movement, TankRightVector);
	//IntendTurnRight(TurnIntend);

	UE_LOG(LogTemp, Warning, TEXT("  MoveComponent Velocity %s"), *MoveVelocity.ToString());
}

