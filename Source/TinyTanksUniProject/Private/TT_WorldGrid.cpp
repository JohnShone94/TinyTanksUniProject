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

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
