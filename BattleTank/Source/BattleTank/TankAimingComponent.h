// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

// Enumerator
UENUM()
enum class EFiringState : uint8
{
	eAiming = 0,
	eLocked,
	eReloading
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(const FVector& AimAtWorldPosition, const float FiringForce);

	bool IsReadyToFire() const;

	//FORCEINLINE void SetBarrelReference(UTankBarrel* BarrelRef)
	//{
	//	TankBarrelComponent = BarrelRef;
	//}

	//FORCEINLINE void SetTurretReference(UTankTurret* TurretRef)
	//{
	//	TankTurretComponent = TurretRef;
	//}

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Setup")
	void Initialize(UTankBarrel* pTankBarrel, UTankTurret* pTankTurret);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// current firing state
	UPROPERTY(BlueprintReadOnly)
	EFiringState FiringState = EFiringState::eLocked;

private:
	// Set the refenrece to the Tank Barrel, this shall be used for the ammo animation
	//UPROPERTY()
	UTankBarrel* TankBarrelComponent = nullptr;
	//UPROPERTY()
	UTankTurret* TankTurretComponent = nullptr;

	void MoveBarrelTo(const FVector& AimDirection);
		
};
