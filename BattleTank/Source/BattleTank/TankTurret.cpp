// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::TurnTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	float NewAzimuth = RelativeSpeed * TurningSpeed * GetWorld()->DeltaTimeSeconds;
	NewAzimuth += RelativeRotation.Yaw;

	UE_LOG(LogTemp, Warning, TEXT(" %f: TurnTurret %f => %f"), GetWorld()->GetTimeSeconds(), RelativeSpeed, NewAzimuth);
	SetRelativeRotation(FRotator(0, NewAzimuth, 0));
}
