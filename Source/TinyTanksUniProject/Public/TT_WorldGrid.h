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
	UPROPERTY(Category = "Default", EditAnywhere)
		float cellSizeX;
	UPROPERTY(Category = "Default", EditAnywhere)
		float cellSizeY;
	UPROPERTY(Category = "Default", EditAnywhere)
		float gridSizeX;
	UPROPERTY(Category = "Default", EditAnywhere)
		float gridSizeY;
	UPROPERTY(Category = "Default", EditAnywhere)
		float gridStartX;
	UPROPERTY(Category = "Default", EditAnywhere)
		float gridStartY;

	UPROPERTY(Category = "Default", EditAnywhere)
		bool activate;
	UPROPERTY(Category = "Default", EditAnywhere)
		bool resetEverything;
	UPROPERTY(Category = "Default", EditAnywhere)
		bool reloadGrid;

	//WARNING: USING THIS IN EDITOR WILL REMOVE ALL THE FLOOR TILES AND RANDOMISE THEM!
	UPROPERTY(Category = "Default", EditAnywhere)
		bool randomiseEveryFloorTile;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_GridCell> gridCell;

	UPROPERTY(VisibleAnywhere)
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

	UFUNCTION(BlueprintCallable)
		TArray<ATT_GridCell*> GetArrayOfEmptyCells();

	UFUNCTION(BlueprintCallable)
		ATT_GridCell* GetRandomEmptyCell();

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR  
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);
#endif

};
