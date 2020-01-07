// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TT_TankSpawnPoint.generated.h"

class ATT_TankBase;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_TankSpawnPoint : public AActor
{
	GENERATED_BODY()

	///////////////////
	//// VARIABLES ////
	///////////////////

public:	

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_TankBase> tanktospawn;

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:	
	ATT_TankSpawnPoint();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		ATT_TankBase* SpawnTank();

protected:
	virtual void BeginPlay() override;
};
