// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TT_TankTurret.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class USphereComponent;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_TankTurret : public APawn
{
	GENERATED_BODY()

	///////////////////
	//// VARIABLES ////
	///////////////////

public:

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float fireRate;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float rotateSpeed;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadwrite)
		FVector turretForwardVector;
	UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
		UStaticMeshComponent* tankGunBase;
	UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
		USceneComponent* fireLocation;

protected:

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:

	ATT_TankTurret();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		FVector GetForwardVector();
	UFUNCTION()
		UStaticMeshComponent* GetTankGunBase() { return tankGunBase; };

protected:
	virtual void BeginPlay() override;
};
