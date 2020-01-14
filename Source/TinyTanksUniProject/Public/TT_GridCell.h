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
};

UENUM()
enum class E_FloorItemToSpawn
{
	FITS_none				UMETA(DiaplayName = "Floor None"),
	FITS_trapdoor			UMETA(DiaplayName = "Trapdoor"),
	FITS_tile				UMETA(DiaplayName = "Floor Tile"),
};


UCLASS()
class TINYTANKSUNIPROJECT_API ATT_GridCell : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		UBoxComponent* box;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* itemSelectionComp;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* floorSelectionComp;
	UPROPERTY(EditAnywhere)
		AActor* currentItemActor;
	UPROPERTY(EditAnywhere)
		AActor* currentFloorActor;

protected:	
	UPROPERTY(EditAnywhere)
		E_ItemToSpawn itemToSpawn;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_TankSpawnPoint> tankSpawnPoint;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_Mine> mine;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_StandardWall> standardWall;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_StandardWall> standardLWall;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_StandardWall> standardTWall;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_DestructableWall> destructableWall;

	UPROPERTY(EditAnywhere)
		E_FloorItemToSpawn floorItemToSpawn;

public:	
	// Sets default values for this actor's properties
	ATT_GridCell();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetBoxSize(float sizeX, float sizeY);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#if WITH_EDITOR  
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);
#endif
};
