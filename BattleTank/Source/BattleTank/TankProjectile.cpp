// Fill out your copyright notice in the Description page of Project Settings.


#include "TankProjectile.h"
#include "TankProjectileMovement.h"

// Sets default values
ATankProjectile::ATankProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create a default subobject
	ProjectileMovement = CreateDefaultSubobject<UTankProjectileMovement>(FName("Projectile Movement"));
	// doesn't move it until we fire it!
	ProjectileMovement->bAutoActivate = false;

}

// Called when the game starts or when spawned
void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATankProjectile::LaunchProjectile(const float FiringForce)
{
	UE_LOG(LogTemp, Warning, TEXT(" %f: Launch projectile with Force %f"), GetWorld()->GetTimeSeconds(), FiringForce);

	// actually apply force on the object so it will be projected according to physics
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * FiringForce);
	ProjectileMovement->AddForce(FVector::ForwardVector * FiringForce);
	// change the "bActivate" attribute to true and object starts moving
	ProjectileMovement->Activate();
}

