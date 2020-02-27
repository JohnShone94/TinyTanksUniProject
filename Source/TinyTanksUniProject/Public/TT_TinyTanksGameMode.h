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

protected:
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		bool bHasGameStarted;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		ATT_MainCamera* mainCam;

	UPROPERTY(Category = "Default | Players", VisibleAnywhere, BlueprintReadOnly)
		bool bCanPlayersControlTanks;

	UPROPERTY(Category = "Default | Players", VisibleAnywhere, BlueprintReadOnly)
		int32 playersLeft;

	UPROPERTY(Category = "Default | Players", VisibleAnywhere, BlueprintReadOnly)
		TMap<int32, ATT_TankBaseController*> playerMap;

	UPROPERTY(Category = "Default | Players", VisibleAnywhere, BlueprintReadOnly)
		TArray<ATT_TankBase*> tankArray;

	UPROPERTY(Category = "Default | Players", VisibleAnywhere, BlueprintReadOnly)
		TArray<ATT_TankTurret*> turretArray;

	UPROPERTY(Category = "Default | Players", VisibleAnywhere, BlueprintReadOnly)
		TArray<ATT_TankBaseController*> playerArray;

	UPROPERTY(Category = "Default | Players", VisibleAnywhere, BlueprintReadOnly)
		int32 teamOneScore;

	UPROPERTY(Category = "Default | Players", VisibleAnywhere, BlueprintReadOnly)
		int32 teamTwoScore;

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:
	ATT_TinyTanksGameMode();

	UFUNCTION()
		void AddPlayerConAtPosition(int32 i, ATT_TankBaseController* pController);

	//called when a tank dies.
	UFUNCTION()
		void RemoveTank(ATT_TankBase* tank, bool addWin);

	//Resets the controllers possessions.
	UFUNCTION(Category = "Gamemode | Players", BlueprintCallable)
		void ResetPlayers();

	UFUNCTION(Category = "Gamemode | Players", BlueprintCallable)
		void PlayerPossessTank();

	UFUNCTION(Category = "Gamemode | Players", BlueprintCallable)
		void SpawnPlayerTanks();

	UFUNCTION(Category = "Gamemode | Players", BlueprintCallable)
		void SpawnPlayerControllers();

	//Tells the player controllers to possess a tank/turret.
	UFUNCTION(Category = "Gamemode | Players", BlueprintCallable)
		void SetupPlayerControllers(bool bOverride = false);

	UFUNCTION(Category = "Gamemode | Game", BlueprintCallable)
		void SetGameStarted(bool started = true) { bHasGameStarted = started; };

	UFUNCTION(Category = "Gamemode | Game", BlueprintCallable)
		void SetCanPlayersControlTanks(bool val) { bCanPlayersControlTanks = val; };

	/////////////
	// GETTERS //
	/////////////

	UFUNCTION(Category = "Gamemode | Players", BlueprintPure)
		bool GetCanPlayersControlTanks() { return bCanPlayersControlTanks; };

	UFUNCTION(Category = "Gamemode | Game", BlueprintPure)
		bool GetGameStarted() { return bHasGameStarted; };

	UFUNCTION(Category = "Gamemode | Players", BlueprintPure)
		TArray<ATT_TankBase*> GetTankArray() { return tankArray; };

	UFUNCTION(Category = "Gamemode | Players", BlueprintPure)
		TArray<ATT_TankTurret*> GetTurretArray() { return turretArray; };

	UFUNCTION(Category = "Gamemode | Game", BlueprintPure)
		ATT_MainCamera* GetMainCamera() { return mainCam;  };

	UFUNCTION(Category = "Gamemode | Players", BlueprintPure)
		int32 GetTeamOneScore() { return teamOneScore; };

	UFUNCTION(Category = "Gamemode | Players", BlueprintPure)
		int32 GetTeamTwoScore() { return teamTwoScore; };

	UFUNCTION(Category = "Gamemode | Players", BlueprintPure)
		int32 GetPlayersLeft() { return playersLeft; };

	UFUNCTION(Category = "Gamemode | Players", BlueprintPure)
		ATT_TankBaseController* GetPlayerConAtPosition(int32 i);

	UFUNCTION(Category = "Gamemode | Players", BlueprintPure)
		int32 GetPlayerPositionFromCon(ATT_TankBaseController* con);

protected:
	virtual void BeginPlay() override;
};
