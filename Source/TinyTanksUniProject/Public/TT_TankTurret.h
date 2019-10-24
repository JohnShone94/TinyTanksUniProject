// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TT_TankTurret.generated.h"

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
		class UStaticMeshComponent* tankGunBase;
	UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* tankGunBarrel;

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:

	ATT_TankTurret();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
