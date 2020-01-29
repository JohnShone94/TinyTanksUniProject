// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_WorldGrid.h"
#include "Engine.h"
#include "TT_GridCell.h"
#include "Components/SceneComponent.h"

ATT_WorldGrid::ATT_WorldGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = sceneComp;



	cellSizeX = 46.5f;
	cellSizeY = 46.5f;
	gridSizeX = 21.0f;
	gridSizeY = 12.0f;
	gridStartX = -463.0f;
	gridStartY = -243.0f;

}

TArray<ATT_GridCell*> ATT_WorldGrid::GetArrayOfEmptyCells()
{
	TArray<ATT_GridCell*> arrayOfEmpty;
	if (cellArray.Num() > 0)
	{
		for (int i = 0; i < cellArray.Num(); i++)
		{
			if (cellArray[i] && cellArray[i]->itemToSpawn == E_ItemToSpawn::ITS_none && cellArray[i]->floorItemToSpawn != E_FloorItemToSpawn::FITS_destroyed)
			{
				arrayOfEmpty.Add(cellArray[i]);
			}
		}

		return arrayOfEmpty;
	}
	return TArray<ATT_GridCell*>();
}

ATT_GridCell* ATT_WorldGrid::GetRandomEmptyCell()
{
	TArray<ATT_GridCell*> arrayOfEmpty;
	if (cellArray.Num() > 0)
	{
		for (int i = 0; i < cellArray.Num(); i++)
		{
			if (cellArray[i] && cellArray[i]->itemToSpawn == E_ItemToSpawn::ITS_none && cellArray[i]->floorItemToSpawn != E_FloorItemToSpawn::FITS_destroyed)
			{
				arrayOfEmpty.Add(cellArray[i]);
			}
		}
	}

	int randNum;

	if (arrayOfEmpty.Num() > 0)
	{
		randNum = FMath::RandRange(0, (arrayOfEmpty.Num() - 1));
		ATT_GridCell* cell = arrayOfEmpty[randNum];
		return cell;
	}

	return nullptr;
}

void ATT_WorldGrid::BeginPlay()
{
	Super::BeginPlay();

}

void ATT_WorldGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#if WITH_EDITOR
void ATT_WorldGrid::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if ((PropertyName == GET_MEMBER_NAME_CHECKED(ATT_WorldGrid, resetEverything)) || (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_WorldGrid, activate)) || (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_WorldGrid, gridStartX)) || (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_WorldGrid, gridStartY)) || (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_WorldGrid, cellSizeX)) || (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_WorldGrid, cellSizeY)) || (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_WorldGrid, gridSizeX)) || (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_WorldGrid, gridSizeY)))
	{
		if (resetEverything)
		{
			if (cellArray.Num() > 0)
			{
				for (int i = 0; i < cellArray.Num(); i++)
				{
					if (cellArray[i])
					{
						if (cellArray[i]->currentFloorActor)
							cellArray[i]->currentFloorActor->Destroy();
						if (cellArray[i]->currentItemActor)
							cellArray[i]->currentItemActor->Destroy();

						cellArray[i]->Destroy();
					}
				}

				cellArray.Empty();
			}

			if (cellLocations.Num() > 0)
				cellLocations.Empty();

			resetEverything = false;
		}

		if (activate)
		{
			if (cellLocations.Num() <= 0)
			{
				for (int x = 0; x < gridSizeX; x++)
				{
					for (int y = 0; y < gridSizeY; y++)
					{
						cellLocations.Add(FVector(gridStartX + (cellSizeX * x), gridStartY + (cellSizeY * y), 0.0f));
					}
				}
			}

			if (cellLocations.Num() > 0 && cellArray.Num() <= 0)
			{
				for (int i = 0; i < cellLocations.Num(); i++)
				{
					FActorSpawnParameters SpawnParams;
					ATT_GridCell* cell = GetWorld()->SpawnActor<ATT_GridCell>(gridCell, FTransform(FRotator(0.0f, 0.0f, 0.0f), cellLocations[i], FVector(1.0f, 1.0f, 1.0f)), SpawnParams);
					if (cell)
					{
						cellArray.Add(cell);
						cell->SetBoxSize(cellSizeX/2, cellSizeY/2);
					}
				}
			}
			else if (cellArray.Num() > 0)
			{
				for (int i = 0; i < cellArray.Num(); i++)
				{
					if (cellArray[i])
						cellArray[i]->HideCell(false);
				}
			}
		}

		if (!activate)
		{
			if (cellArray.Num() > 0)
			{
				for (int i = 0; i < cellArray.Num(); i++)
				{
					if (cellArray[i])
						cellArray[i]->HideCell(true);
				}
			}
		}
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_WorldGrid, randomiseEveryFloorTile))
	{
		if (cellArray.Num() > 0)
		{
			for (int i = 0; i < cellArray.Num(); i++)
			{
				if (cellArray[i] && (cellArray[i]->floorItemToSpawn == E_FloorItemToSpawn::FITS_tile || cellArray[i]->floorItemToSpawn == E_FloorItemToSpawn::FITS_none))
					cellArray[i]->RandomiseFloorTile();
			}
		}
		randomiseEveryFloorTile = false;
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_WorldGrid, reloadGrid))
	{
		if (cellArray.Num() > 0)
		{
			for (int i = 0; i < cellArray.Num(); i++)
			{
				if (cellArray[i])
					cellArray[i]->ReloadCell();
			}
		}
		reloadGrid = false;
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
