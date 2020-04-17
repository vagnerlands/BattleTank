// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(const FVector& AimAtWorldPosition, const float FiringForce);

	FORCEINLINE void SetBarrelReference(UStaticMeshComponent* BarrelRef)
	{
		TankBarrelComponent = BarrelRef;
	}

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Set the refenrece to the Tank Barrel, this shall be used for the ammo animation
	UPROPERTY()
	UStaticMeshComponent* TankBarrelComponent = nullptr;
		
};
