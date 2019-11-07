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
	
public:	
	// Sets default values for this actor's properties
	ATT_TankSpawnPoint();

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_TankBase> tanktospawn;

	UFUNCTION()
		ATT_TankBase* SpawnTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
