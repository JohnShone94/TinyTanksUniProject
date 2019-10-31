// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TT_TankBaseController.generated.h"


class ATT_TankBase;
class ATT_TankTurret;
class ATT_TinyTanksGameMode;
class APawn;
/**
 * 
 */
UCLASS()
class TINYTANKSUNIPROJECT_API ATT_TankBaseController : public APlayerController
{
	GENERATED_BODY()
	
	///////////////////
	//// VARIABLES ////
	///////////////////

protected:
	static const FName moveBinding;
	static const FName rotateBinding;
	static const FName fireBinding;

	UPROPERTY()
		ATT_TankBase* tankPawn;
	UPROPERTY()
		ATT_TankTurret* turretPawn;
	UPROPERTY()
		ATT_TinyTanksGameMode* gameMode;

	/* Flag to control firing  */
	uint32 bCanFire : 1;
	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:
	ATT_TankBaseController();

	UFUNCTION()
		void SetTankPawn(ATT_TankBase* tank) { tankPawn = tank; };
	UFUNCTION()
		void SetTurretPawn(ATT_TankTurret* turret) { turretPawn = turret; };

protected:

	virtual void BeginPlay() override;

	//virtual void PlayerTick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	void MoveForward(float val);
	void Rotate(float val);
	void FireShot(float val);

	void ShotTimerExpired();
};
