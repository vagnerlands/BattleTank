// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"

class ATankProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(const FVector& HitLocation);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelRef);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretReference);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(BlueprintCallable)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Set the speed of the projectile..
	UPROPERTY(EditAnywhere, Category = Setup)
	float FiringForce = 10000.f;

	// reference to the projectile blueprint
	UPROPERTY(EditAnywhere, Category = Firing)
	TSubclassOf< ATankProjectile > ProjectileBP;

	// local tank barrel
	UTankBarrel* Barrel = nullptr;
};
