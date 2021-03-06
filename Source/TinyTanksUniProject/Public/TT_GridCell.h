// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_GridCell.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

class ATT_TankSpawnPoint;
class ATT_Mine;
class ATT_StandardWall;
class ATT_DestructableWall;
class ATT_FloorTile;
class ATT_TrapDoor;
class ATT_Spike;

UENUM()
enum class E_ItemToSpawn
{
	ITS_none				UMETA(DiaplayName = "None"),
	ITS_straightWall		UMETA(DiaplayName = "Straight Wall"),
	ITS_tJunctionWall		UMETA(DiaplayName = "T Junction Wall"),
	ITS_lJunctionWall		UMETA(DiaplayName = "L Junction Wall"),
	ITS_destructableWall	UMETA(DiaplayName = "Destructable Wall"),
	ITS_spawnPoint			UMETA(DiaplayName = "Spawn Point"),
	ITS_mine				UMETA(DiaplayName = "Mine"),
	ITS_destroyed			UMETA(DiaplayName = "Destroyed"),
	ITS_filled				UMETA(DiaplayName = "Filled"),
};

UENUM()
enum class E_FloorItemToSpawn
{
	FITS_none				UMETA(DiaplayName = "No Tile"),
	FITS_trapdoor			UMETA(DiaplayName = "Trapdoor Tile"),
	FITS_tile				UMETA(DiaplayName = "Floor Tile"),
	FITS_spike			UMETA(DiaplayName = "Spike Tile"),
	FITS_destroyed			UMETA(DiaplayName = "Floor Destroyed"),
};


UCLASS()
class TINYTANKSUNIPROJECT_API ATT_GridCell : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "Default | SpawnItems", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_TankSpawnPoint> tankSpawnPoint;
	UPROPERTY(Category = "Default | SpawnItems", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_Mine> mine;
	UPROPERTY(Category = "Default | SpawnItems", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_StandardWall> standardWall;
	UPROPERTY(Category = "Default | SpawnItems", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_StandardWall> standardLWall;
	UPROPERTY(Category = "Default | SpawnItems", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_StandardWall> standardTWall;
	UPROPERTY(Category = "Default | SpawnItems", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_DestructableWall> destructableWall;
	UPROPERTY(Category = "Default | SpawnItems", EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<ATT_FloorTile>> floorTiles;
	UPROPERTY(Category = "Default | SpawnItems", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_TrapDoor> trapDoor;
	UPROPERTY(Category = "Default | SpawnItems", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_Spike> spikeTile;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		E_ItemToSpawn itemToSpawn;
	UPROPERTY(Category = "Default", EditAnywhere)
		E_FloorItemToSpawn floorItemToSpawn;

	UPROPERTY(Category = "Default", EditAnywhere)
		bool rotateRight;
	UPROPERTY(Category = "Default", EditAnywhere)
		bool rotateLeft;

	UPROPERTY(Category = "Default", VisibleAnywhere)
		AActor* currentItemActor;
	UPROPERTY(Category = "Default", VisibleAnywhere)
		AActor* currentFloorActor;


	UPROPERTY()
		int32 rotationVal;

protected:	

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* box;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* itemSelectionComp;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* floorSelectionComp;
public:	
	// Sets default values for this actor's properties
	ATT_GridCell();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetBoxSize(float sizeX, float sizeY);

	UFUNCTION(BlueprintCallable)
		void RandomiseFloorTile();

	UFUNCTION(BlueprintCallable)
		void ReloadCell();

	UFUNCTION(BlueprintCallable)
		void HideCell(bool val);

	UFUNCTION(BlueprintCallable)
		void SetCellFilled(bool val = true);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#if WITH_EDITOR  
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);
#endif
};
