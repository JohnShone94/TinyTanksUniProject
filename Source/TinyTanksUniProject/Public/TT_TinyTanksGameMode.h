// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TT_TinyTanksGameMode.generated.h"

class ATT_TankBaseController;
class ATT_TankBase;
class ATT_TankTurret;
class ATT_MainCamera;

/**
 * 
 */
UCLASS()
class TINYTANKSUNIPROJECT_API ATT_TinyTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

	///////////////////
	//// VARIABLES ////
	///////////////////

public:
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TMap<int32, ATT_TankBaseController*> playerMap;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TArray<ATT_TankBase*> tankArray;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TArray<ATT_TankTurret*> turretArray;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TArray<ATT_TankBaseController*> playerArray;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		ATT_TankBase* tanktospawn;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		ATT_MainCamera* mainCam;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		int32 teamBlueScore;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		int32 teamRedScore;

protected:
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		bool bCanPlayersControlTanks;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		int32 playersLeft;

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:
	ATT_TinyTanksGameMode();

	UFUNCTION()
		void AddPlayerConAtPosition(int32 i, ATT_TankBaseController* pController);

	//Resets the controllers possessions.
	UFUNCTION(BlueprintCallable)
		void ResetPlayers();

	//Tells the player controllers to posses a tank/turret.
	UFUNCTION(BlueprintCallable)
		void SetupPlayerControllers(bool bOverride = false);

	UFUNCTION()
		ATT_TankBaseController* GetPlayerConAtPosition(int32 i);
	
	UFUNCTION()
		int32 GetPlayerPositionFromCon(ATT_TankBaseController* con);

	//called when a tank dies.
	UFUNCTION()
		void RemoveTank(ATT_TankBase* tank);

	UFUNCTION()
		int32 GetPlayersLeft() { return playersLeft; };

	UFUNCTION(BlueprintCallable)
		void PlayerPossessTank();

	UFUNCTION(BlueprintCallable)
		bool GetCanPlayersControlTanks() { return bCanPlayersControlTanks; };

	UFUNCTION(BlueprintCallable)
		void SetCanPlayersControlTanks(bool val) { bCanPlayersControlTanks = val; };
	UFUNCTION(BlueprintCallable)
		void SpawnPlayerTanks();
	UFUNCTION(BlueprintCallable)
		void SpawnPlayerControllers();

protected:
	virtual void BeginPlay() override;
};
