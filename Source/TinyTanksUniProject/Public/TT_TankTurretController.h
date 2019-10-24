// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TT_TankTurretController.generated.h"

class ATT_TankTurret;

/**
 * 
 */
UCLASS()
class TINYTANKSUNIPROJECT_API ATT_TankTurretController : public APlayerController
{
	GENERATED_BODY()

	///////////////////
	//// VARIABLES ////
	///////////////////

protected:

	static const FName rotateBinding;
	static const FName fireBinding;

	UPROPERTY()
		ATT_TankTurret* controlledPawn;

	/* Flag to control firing  */
	uint32 bCanFire : 1;
	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:
	ATT_TankTurretController();

protected:

	virtual void BeginPlay() override;

	virtual void PlayerTick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	void FireShot(FVector FireDirection);

	void ShotTimerExpired();
};
