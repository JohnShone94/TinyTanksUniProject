// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TT_TankTurret.generated.h"

class ATT_BasicBullet;
class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_TankTurret : public APawn
{
	GENERATED_BODY()

	///////////////////
	//// VARIABLES ////
	///////////////////

public:

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		FVector gunOffset;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float fireRate;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float rotateSpeed;
	UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FVector turretForwardVector;

protected:

	UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* tankGunBase;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* fireLocation;

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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
