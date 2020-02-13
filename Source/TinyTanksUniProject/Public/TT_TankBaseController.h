// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TT_TankBaseController.generated.h"


class ATT_TankTurret;
class ATT_TankBase;
class ATT_TinyTanksGameMode;
class APawn;

UENUM(BlueprintType)
enum class EPowerupType : uint8
{
	PT_none						UMETA(DiaplayName = "None"),

	PT_speedBoost				UMETA(DisplayName = "Speed Boost | Neutral"),

	PT_airblast					UMETA(DisplayName = "Airblast | Defensive"),
	PT_shild					UMETA(DisplayName = "Shild | Defensive"),
	PT_smokeScreen				UMETA(DisplayName = "Smoke Screen | Defensive"),
	PT_floating					UMETA(DisplayName = "Floating | Defensive"),

	PT_fastBullet				UMETA(DisplayName = "Fast Bullet | Offensive"),
	PT_missileBullet			UMETA(DisplayName = "Misslie Bullet | Offensive"),
	PT_stunBullet				UMETA(DisplayName = "Stun Bullet | Offensive"),
	PT_undergroundBullet		UMETA(DisplayName = "Undeground Bullet | Offensive"),
};

UENUM(BlueprintType)
enum class ESelectedTeam : uint8
{
	ST_none						UMETA(DiaplayName = "No Team"),

	ST_blueBase					UMETA(DisplayName = "Blue Team | Base"),
	ST_blueTurret				UMETA(DisplayName = "Blue Team | Turret"),

	ST_greenBase				UMETA(DisplayName = "Green Team | Base"),
	ST_greenTurret				UMETA(DisplayName = "Green Team | Turret"),

};


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


	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		bool bHasFast;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		bool bHasMissile;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		ESelectedTeam selectedTeam;

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

	UFUNCTION(BlueprintCallable)
		void SetPlayerTeam(ESelectedTeam team) { selectedTeam = team; };

	UFUNCTION(BlueprintCallable)
		ESelectedTeam GetPlayerTeam() { return selectedTeam; };

	//UFUNCTION()
	//	void PickupMissile();
	//UFUNCTION()
	//	void PickupFast();

protected:


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
