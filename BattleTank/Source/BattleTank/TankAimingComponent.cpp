// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UTankAimingComponent::IsReadyToFire() const
{
	bool bRetVal = false;

	if ((FiringState == EFiringState::eAiming) || (FiringState == EFiringState::eLocked))
	{
		bRetVal = true;
	}

	return bRetVal;
}

void UTankAimingComponent::Initialize(UTankBarrel* pTankBarrel, UTankTurret* pTankTurret)
{
	TankBarrelComponent = pTankBarrel;
	TankTurretComponent = pTankTurret;
}

void UTankAimingComponent::AimAt(const FVector& AimAtWorldPosition, const float FiringForce)
{
	if (!TankBarrelComponent) { return; }

	FVector OutVelocity(0);
	FVector StartLocation = TankBarrelComponent->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(
			GetWorld(),
			OutVelocity,
			StartLocation,
			AimAtWorldPosition,
			FiringForce,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		) // end of SuggestProjectileVelocity
	) // end of if clause
	{	
		FVector AimDirection = OutVelocity.GetSafeNormal();
		MoveBarrelTo(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT(" %f: Tank (%s) firing direction (%s) "), GetWorld()->GetTimeSeconds(), *GetOwner()->GetName(), *AimDirection.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(" %f: Not possible to calculate ProjectileVelocity "), GetWorld()->GetTimeSeconds());
	}
	//UE_LOG(LogTemp, Warning, TEXT(" Tank (%s) has a barrel at (%s) "), *GetOwner()->GetName(), *TankBarrelComponent->GetComponentLocation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT(" Tank (%s) aims at (%s)"), *GetOwner()->GetName(), *AimAtWorldPosition.ToString());
}

void UTankAimingComponent::MoveBarrelTo(const FVector& AimDirection)
{
	FRotator BarrelRotation = TankBarrelComponent->GetForwardVector().Rotation();
	FRotator AimDirectionRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimDirectionRotator - BarrelRotation;
	// don't care about the pitch itself, whatever comes in will be clamped
	TankBarrelComponent->ElevateBarrel(DeltaRotator.Pitch);
	// always try to find the shortest path to the azimuth, in order to avoid 
	if (FMath::Abs(DeltaRotator.Yaw) > 180.F)
	{
		DeltaRotator.Yaw *= -1.F;
	}
	TankTurretComponent->TurnTurret(DeltaRotator.Yaw);
}


