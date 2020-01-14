// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_WorldGrid.generated.h"

class ATT_GridCell;
class USceneComponent;
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
	UPROPERTY(EditAnywhere)
		float gridStartX;
	UPROPERTY(EditAnywhere)
		float gridStartY;
	UPROPERTY(EditAnywhere)
		bool activate;
	UPROPERTY(EditAnywhere)
		bool resetEverything;

	UPROPERTY(EditAnywhere)
		USceneComponent* sceneComp;

protected:

	UPROPERTY(EditAnywhere)
		TArray<FVector> cellLocations;

	UPROPERTY(EditAnywhere)
		TArray<ATT_GridCell*> cellArray;


	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:
	ATT_WorldGrid();

	UFUNCTION(BlueprintCallable)
		TArray<FVector> GetArrayOfCellLocations() { return cellLocations; };

	UFUNCTION(BlueprintCallable)
		TArray<ATT_GridCell*> GetArrayOfCells() { return cellArray; };

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR  
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);
#endif

};
