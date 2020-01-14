// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_GridCell.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TT_StandardWall.h"
#include "TT_DestructableWall.h"
#include "TT_Mine.h"
#include "TT_TankSpawnPoint.h"

// Sets default values
ATT_GridCell::ATT_GridCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = box;

	itemSelectionComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Selection Comp"));
	itemSelectionComp->SetupAttachment(RootComponent);

	floorSelectionComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor Selection Comp"));
	floorSelectionComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATT_GridCell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATT_GridCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATT_GridCell::SetBoxSize(float sizeX, float sizeY)
{
	if (box)
		box->SetBoxExtent(FVector(sizeX, sizeY, 10.0f));
}

#if WITH_EDITOR
void ATT_GridCell::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_GridCell, itemSelectionComp) || PropertyName == GET_MEMBER_NAME_CHECKED(ATT_GridCell, floorSelectionComp))
	{
		itemSelectionComp->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
		itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

		floorSelectionComp->SetRelativeScale3D(FVector(0.45f, 0.45f, 0.05f));
		floorSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_GridCell, itemToSpawn))
	{

		switch (itemToSpawn)
		{
		case E_ItemToSpawn::ITS_none:
		{
			if (currentItemActor)
			{
				currentItemActor->Destroy();
				currentItemActor = nullptr;
			}

			itemSelectionComp->SetVisibility(true);

			break;
		}
		case E_ItemToSpawn::ITS_straightWall:
		{
			if (currentItemActor)
			{
				currentItemActor->Destroy();
				currentItemActor = nullptr;
			}

			FActorSpawnParameters SpawnParams;

			ATT_StandardWall* actorRef = GetWorld()->SpawnActor<ATT_StandardWall>(standardWall, GetTransform(), SpawnParams);
			currentItemActor = actorRef;

			itemSelectionComp->SetVisibility(false);

			break;
		}
		case E_ItemToSpawn::ITS_tJunctionWall:
		{
			if (currentItemActor)
			{
				currentItemActor->Destroy();
				currentItemActor = nullptr;
			}

			FActorSpawnParameters SpawnParams;

			ATT_StandardWall* actorRef = GetWorld()->SpawnActor<ATT_StandardWall>(standardTWall, GetTransform(), SpawnParams);
			currentItemActor = actorRef;

			itemSelectionComp->SetVisibility(false);

			break;
		}
		case E_ItemToSpawn::ITS_lJunctionWall:
		{
			if (currentItemActor)
			{
				currentItemActor->Destroy();
				currentItemActor = nullptr;
			}

			FActorSpawnParameters SpawnParams;

			ATT_StandardWall* actorRef = GetWorld()->SpawnActor<ATT_StandardWall>(standardLWall, GetTransform(), SpawnParams);
			currentItemActor = actorRef;

			itemSelectionComp->SetVisibility(false);

			break;
		}
		case E_ItemToSpawn::ITS_destructableWall:
		{
			if (currentItemActor)
			{
				currentItemActor->Destroy();
				currentItemActor = nullptr;
			}

			FActorSpawnParameters SpawnParams;

			ATT_DestructableWall* actorRef = GetWorld()->SpawnActor<ATT_DestructableWall>(destructableWall, GetTransform(), SpawnParams);
			currentItemActor = actorRef;

			itemSelectionComp->SetVisibility(false);

			break;
		}
		case E_ItemToSpawn::ITS_spawnPoint:
		{
			if (currentItemActor)
			{
				currentItemActor->Destroy();
				currentItemActor = nullptr;
			}

			FActorSpawnParameters SpawnParams;

			ATT_TankSpawnPoint* actorRef = GetWorld()->SpawnActor<ATT_TankSpawnPoint>(tankSpawnPoint, GetTransform(), SpawnParams);
			currentItemActor = actorRef;

			itemSelectionComp->SetVisibility(false);

			break;
		}
		case E_ItemToSpawn::ITS_mine:
		{
			if (currentItemActor)
			{
				currentItemActor->Destroy();
				currentItemActor = nullptr;
			}

			FActorSpawnParameters SpawnParams;

			ATT_Mine* actorRef = GetWorld()->SpawnActor<ATT_Mine>(mine, GetTransform(), SpawnParams);
			currentItemActor = actorRef;

			itemSelectionComp->SetVisibility(false);

			break;
		}
		default:
			break;
		}
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_GridCell, floorItemToSpawn))
	{
		switch (floorItemToSpawn)
		{
		case E_FloorItemToSpawn::FITS_none:
		{
			if (currentFloorActor)
			{
				currentFloorActor->Destroy();
				currentFloorActor = nullptr;
			}

			itemSelectionComp->SetVisibility(true);

			floorSelectionComp->SetVisibility(false);
			break;
		}
		case E_FloorItemToSpawn::FITS_trapdoor:
		{
			floorSelectionComp->SetVisibility(false);
			break;
		}
		case E_FloorItemToSpawn::FITS_tile:
		{
			floorSelectionComp->SetVisibility(false);
			break;
		}
		default:
			break;
		}
	}

}
#endif