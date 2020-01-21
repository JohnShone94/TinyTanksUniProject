// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TT_TankBase.h"
#include "GameFramework/PlayerController.h"
#include "TT_TankBaseController.generated.h"


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
	static const FName activateSpecialBinding;
	static const FName useSpecialBinding;

	UPROPERTY()
		ATT_TankBase* tankPawn;
	UPROPERTY()
		ATT_TankTurret* turretPawn;
	UPROPERTY()
		ATT_TinyTanksGameMode* gameMode;

	//Set when the base is rotating, used to stop the player from moving while rotating.
	UPROPERTY()
		bool rotatingBase;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		EPowerupType activeOffensivePowerup;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		EPowerupType activeDeffensivePowerup;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		EPowerupType activeNeutralPowerup;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float airblastSphereRadius;

	//Used to control the fireing.
	uint32 bCanFire : 1;

	//Handler for the timer.
	FTimerHandle TimerHandle_ShotTimerExpired;

	//Handler for the timer.
	FTimerHandle TimerHandle_SpecialTimerExpired;

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:
	ATT_TankBaseController();

	UFUNCTION()
		void SetTankPawn(ATT_TankBase* tank) { tankPawn = tank; };
	UFUNCTION()
		void SetTurretPawn(ATT_TankTurret* turret) { turretPawn = turret; };

	//UFUNCTION()
	//	void PickupMissile();
	//UFUNCTION()
	//	void PickupFast();

protected:

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		bool bHasFast;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		bool bHasMissile;


	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
	UFUNCTION(BlueprintCallable)
		void MoveForward(float val);
	UFUNCTION(BlueprintCallable)
		void Rotate(float val);
	UFUNCTION(BlueprintCallable)
		void FireShot(float val);
	UFUNCTION(BlueprintCallable)
		void ActivateSpecial(float val);
	UFUNCTION(BlueprintCallable)
		void UseSpecial(float val);

	void ShotTimerExpired();
	void SpecialTimerExpired();

};
