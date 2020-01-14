// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_WorldGrid.generated.h"

class UBoxComponent;

/**
 * 
 */
UCLASS()
class TINYTANKSUNIPROJECT_API ATT_WorldGrid : public AActor
{
	GENERATED_BODY()
	///////////////////
	//// VARIABLES ////
	///////////////////

public:
	UPROPERTY(EditAnywhere)
		float cellSizeX;
	UPROPERTY(EditAnywhere)
		float cellSizeY;
	UPROPERTY(EditAnywhere)
		float gridSizeX;
	UPROPERTY(EditAnywhere)
		float gridSizeY;

protected:
	UPROPERTY(EditAnywhere)
		UBoxComponent* box;

	UPROPERTY(EditAnywhere)
		TArray<UBoxComponent*> cellArray;


	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:
	ATT_WorldGrid();

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR  
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);
#endif

};
