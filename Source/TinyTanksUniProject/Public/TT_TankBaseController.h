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

	PT_shild					UMETA(DisplayName = "Shild | Defensive"),
	PT_floating					UMETA(DisplayName = "Floating | Defensive"),

	//PT_smokeScreen			UMETA(DisplayName = "Smoke Screen | Defensive"),
	//PT_speedBoost				UMETA(DisplayName = "Speed Boost | Defensive"),
	//PT_airblast				UMETA(DisplayName = "Airblast | Defensive"),

	PT_missileBullet			UMETA(DisplayName = "Misslie Bullet | Offensive"),
	PT_stunBullet				UMETA(DisplayName = "Stun Bullet | Offensive"),

	//PT_fastBullet				UMETA(DisplayName = "Fast Bullet | Offensive"),
	//PT_undergroundBullet		UMETA(DisplayName = "Undeground Bullet | Offensive"),
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
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		ESelectedTeam selectedTeam;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		ATT_TankBase* tankPawn;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		ATT_TankTurret* turretPawn;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		ATT_TinyTanksGameMode* gameMode;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		EPowerupType activeOffensivePowerup;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		EPowerupType activeDeffensivePowerup;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		float speedMultiplier;

private:
	//Used to control the fireing.
	uint32 bCanFire : 1;

	//Handler for the timer.
	FTimerHandle fireMissileTimerHandle;

	//Handler for the timer.
	FTimerHandle powerupTimerHandle;

	float i;

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:
	ATT_TankBaseController();

	UFUNCTION(Category = "PlayerCon", BlueprintCallable)
		void SetTankPawn(ATT_TankBase* tank) { tankPawn = tank; };
	UFUNCTION(Category = "PlayerCon", BlueprintCallable)
		void SetTurretPawn(ATT_TankTurret* turret) { turretPawn = turret; };
	UFUNCTION(Category = "PlayerCon", BlueprintCallable)
		void SetPlayerTeam(ESelectedTeam team) { selectedTeam = team; };
	UFUNCTION(Category = "PlayerCon", BlueprintCallable)
		ESelectedTeam GetPlayerTeam() { return selectedTeam; };

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	
	UFUNCTION(Category = "PlayerCon", BlueprintCallable)
		void MoveForward(float val);
	UFUNCTION(Category = "PlayerCon", BlueprintCallable)
		void Rotate(float val);
	UFUNCTION(Category = "PlayerCon", BlueprintCallable)
		void FireShot(float val);
	UFUNCTION(Category = "PlayerCon", BlueprintCallable)
		void ActivateSpecial(float val);
	UFUNCTION(Category = "PlayerCon", BlueprintCallable)
		void UseSpecial(float val);

private:
	void ShotTimerExpired();
	void SpecialTimerExpired();

};
