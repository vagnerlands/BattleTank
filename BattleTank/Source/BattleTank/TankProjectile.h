// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankProjectile.generated.h"

class UTankProjectileMovement;

UCLASS()
class BATTLETANK_API ATankProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// receives the fire force, this is how far the projectile can travel distances
	void LaunchProjectile(const float FiringForce);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UTankProjectileMovement* ProjectileMovement = nullptr;

};
