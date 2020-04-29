// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankBarrel.h"
#include "TankMovementComponent.h"
#include "TankProjectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// create a default aiming component for the blueprint
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::Fire()
{
	if (!Barrel) { return; }
	// did we manage to reload the tank yet?
	const bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > TankReloadTime;
	
	if (isReloaded)
	{
		FVector ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));
		// creates an actor "projectile"
		ATankProjectile* ProjectileObject = GetWorld()->SpawnActor<ATankProjectile>(ProjectileBP, ProjectileLocation, ProjectileRotation);
		// Actually shoots the projectile
		ProjectileObject->LaunchProjectile(FiringForce);
		// Update the last fire time for reload purposes
		LastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::AimAt(const FVector& HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, FiringForce);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelRef)
{
	// keeps a local reference in tank too
	Barrel = BarrelRef;
	// pass the reference to aiming component
	TankAimingComponent->SetBarrelReference(BarrelRef);
}

void ATank::SetTurretReference(UTankTurret* TurretReference)
{
	TankAimingComponent->SetTurretReference(TurretReference);
}
