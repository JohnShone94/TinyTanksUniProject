// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TT_TinyTanksGameMode.generated.h"

class ATT_TankBaseController;
class ATT_TankBase;
class ATT_TankTurret;

/**
 * 
 */
UCLASS()
class TINYTANKSUNIPROJECT_API ATT_TinyTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

		ATT_TinyTanksGameMode();

public:
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TMap<int32, ATT_TankBaseController*> playerMap;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		ATT_TankBase* tankOne;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		ATT_TankBase* tankTwo;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		ATT_TankTurret* turretOne;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		ATT_TankTurret* turretTwo;

protected:
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		bool bCanPlayersControlTanks;


public:
	UFUNCTION()
		void AddPlayerConAtPosition(int32 i, ATT_TankBaseController* pController);

	UFUNCTION()
		ATT_TankBaseController* GetPlayerConAtPosition(int32 i);
	
	UFUNCTION()
		int32 GetPlayerPositionFromCon(ATT_TankBaseController* con);

	UFUNCTION()
		void AddTankToGM(ATT_TankBase* tank);

	UFUNCTION(BlueprintCallable)
		bool GetCanPlayersControlTanks() { return bCanPlayersControlTanks; };

	UFUNCTION(BlueprintCallable)
		void SetCanPlayersControlTanks(bool val) { bCanPlayersControlTanks = val; };


protected:
	virtual void BeginPlay() override;
};
