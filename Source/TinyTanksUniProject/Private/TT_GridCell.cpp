// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_GridCell.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TT_StandardWall.h"
#include "TT_FloorTile.h"
#include "TT_DestructableWall.h"
#include "TT_Mine.h"
#include "TT_TankSpawnPoint.h"
#include "TT_TrapDoor.h"
#include "TT_Spike.h"

// Sets default values
ATT_GridCell::ATT_GridCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = box;

	itemSelectionComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Selection Comp"));
	itemSelectionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	itemSelectionComp->SetupAttachment(RootComponent);

	itemSelectionComp->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 31.0f));

	floorSelectionComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor Selection Comp"));
	floorSelectionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	floorSelectionComp->SetupAttachment(RootComponent);

	floorSelectionComp->SetRelativeScale3D(FVector(0.465f, 0.465f, 0.05f));
	floorSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 1.0f));
}

// Called when the game starts or when spawned
void ATT_GridCell::BeginPlay()
{
	Super::BeginPlay();

	if (itemSelectionComp)
		itemSelectionComp->SetVisibility(false);
	if (floorSelectionComp)
		floorSelectionComp->SetVisibility(false);
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

void ATT_GridCell::RandomiseFloorTile()
{
	floorItemToSpawn = E_FloorItemToSpawn::FITS_tile;

	if (currentFloorActor)
	{
		currentFloorActor->Destroy();
		currentFloorActor = nullptr;
	}

	if(floorSelectionComp)
		floorSelectionComp->SetVisibility(false);

	FActorSpawnParameters SpawnParams;

	ATT_FloorTile* actorRef = GetWorld()->SpawnActor<ATT_FloorTile>(floorTile, GetTransform(), SpawnParams);
	currentFloorActor = actorRef;
}

void ATT_GridCell::ReloadCell()
{
	if (currentItemActor)
	{
		FTransform newLoc = FTransform(GetActorRotation(), (FVector(GetTransform().GetLocation().X, GetTransform().GetLocation().Y, 30.0f)), FVector(1.0f, 1.0f, 1.0f));

		if(itemSelectionComp)
			itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 94.0f));
	
		if (itemToSpawn == E_ItemToSpawn::ITS_spawnPoint)
		{
			FVector newNewLoc = FVector((newLoc.GetLocation().X), (newLoc.GetLocation().Y), (newLoc.GetLocation().Z + 16.0f));
			currentItemActor->SetActorLocation(newNewLoc);
		}
		else
			currentItemActor->SetActorLocation(newLoc.GetLocation());
	}
	else
	{
		if(itemToSpawn == E_ItemToSpawn::ITS_destroyed && itemSelectionComp)
			itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 94.0f));
		else
			itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 31.0f));
	}

	if (currentFloorActor)
	{
		if (floorSelectionComp)
			floorSelectionComp->SetRelativeScale3D(FVector(0.465f, 0.465f, 0.05f));

		if (floorItemToSpawn == E_FloorItemToSpawn::FITS_trapdoor)
		{
			FTransform newLoc = FTransform(GetActorRotation(), (FVector(GetTransform().GetLocation().X, GetTransform().GetLocation().Y, 26.0f)), FVector(1.0f, 1.0f, 1.0f));
			currentFloorActor->SetActorLocation(newLoc.GetLocation());
		}
		else
			currentFloorActor->SetActorLocation(GetActorLocation());
	}
	else if(floorSelectionComp)
		floorSelectionComp->SetRelativeScale3D(FVector(0.465f, 0.465f, 0.05f));
}

void ATT_GridCell::HideCell(bool val)
{
	if (itemSelectionComp)
		itemSelectionComp->SetVisibility(!val);
	if (floorSelectionComp && floorItemToSpawn == E_FloorItemToSpawn::FITS_none)
		floorSelectionComp->SetVisibility(!val);
}


#if WITH_EDITOR
void ATT_GridCell::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_GridCell, itemSelectionComp) || PropertyName == GET_MEMBER_NAME_CHECKED(ATT_GridCell, floorSelectionComp))
	{
		itemSelectionComp->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
		itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 31.0f));

		floorSelectionComp->SetRelativeScale3D(FVector(0.465f, 0.465f, 0.05f));
		floorSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 1.0f));
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_GridCell, itemToSpawn))
	{
		FTransform newLoc = FTransform(GetActorRotation(), (FVector(GetTransform().GetLocation().X, GetTransform().GetLocation().Y, 30.0f)), FVector(1.0f, 1.0f, 1.0f));
		switch (itemToSpawn)
		{
			case E_ItemToSpawn::ITS_none:
			{
				if (currentItemActor)
				{
					currentItemActor->Destroy();
					currentItemActor = nullptr;
				}

				itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 31.0f));

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

				ATT_StandardWall* actorRef = GetWorld()->SpawnActor<ATT_StandardWall>(standardWall, newLoc, SpawnParams);
				currentItemActor = actorRef;

				itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 94.0f));

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

				ATT_StandardWall* actorRef = GetWorld()->SpawnActor<ATT_StandardWall>(standardTWall, newLoc, SpawnParams);
				currentItemActor = actorRef;

				itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 94.0f));

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

				ATT_StandardWall* actorRef = GetWorld()->SpawnActor<ATT_StandardWall>(standardLWall, newLoc, SpawnParams);
				currentItemActor = actorRef;

				itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 94.0f));

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

				ATT_DestructableWall* actorRef = GetWorld()->SpawnActor<ATT_DestructableWall>(destructableWall, newLoc, SpawnParams);
				currentItemActor = actorRef;

				itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 94.0f));

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

				FVector newNewLoc = FVector((newLoc.GetLocation().X), (newLoc.GetLocation().Y), (newLoc.GetLocation().Z + 16.0f));

				ATT_TankSpawnPoint* actorRef = GetWorld()->SpawnActor<ATT_TankSpawnPoint>(tankSpawnPoint, FTransform(GetTransform().GetRotation(), newNewLoc, GetTransform().GetScale3D()), SpawnParams);
				currentItemActor = actorRef;

				itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 94.0f));

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

				ATT_Mine* actorRef = GetWorld()->SpawnActor<ATT_Mine>(mine, newLoc, SpawnParams);
				currentItemActor = actorRef;

				itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 94.0f));

				break;
			}
			case E_ItemToSpawn::ITS_destroyed:
			{
				if (currentItemActor)
				{
					currentItemActor->Destroy();
					currentItemActor = nullptr;
				}

				itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 94.0f));

				break;
			}
			default:
			{
				if (currentItemActor)
				{
					currentItemActor->Destroy();
					currentItemActor = nullptr;
				}

				itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 31.0f));

				break;
			}
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

				floorSelectionComp->SetVisibility(true);
				break;
			}
			case E_FloorItemToSpawn::FITS_trapdoor:
			{
				FTransform newLoc = FTransform(GetActorRotation(), (FVector(GetTransform().GetLocation().X, GetTransform().GetLocation().Y, 26.0f)), FVector(1.0f, 1.0f, 1.0f));

				if (currentFloorActor)
				{
					currentFloorActor->Destroy();
					currentFloorActor = nullptr;
				}

				if (floorSelectionComp)
					floorSelectionComp->SetVisibility(false);

				FActorSpawnParameters SpawnParams;

				ATT_TrapDoor* actorRef = GetWorld()->SpawnActor<ATT_TrapDoor>(trapDoor, newLoc, SpawnParams);
				currentFloorActor = actorRef;

				break;
			}
			case E_FloorItemToSpawn::FITS_spike:
			{
				FTransform newLoc = FTransform(GetActorRotation(), (FVector(GetTransform().GetLocation().X, GetTransform().GetLocation().Y, 26.0f)), FVector(1.0f, 1.0f, 1.0f));

				if (currentFloorActor)
				{
					currentFloorActor->Destroy();
					currentFloorActor = nullptr;
				}

				if (floorSelectionComp)
					floorSelectionComp->SetVisibility(false);

				FActorSpawnParameters SpawnParams;

				ATT_Spike* actorRef = GetWorld()->SpawnActor<ATT_Spike>(spikeTile, GetTransform(), SpawnParams);
				currentFloorActor = actorRef;

				break;
			}
			case E_FloorItemToSpawn::FITS_tile:
			{
				floorSelectionComp->SetVisibility(false);
				RandomiseFloorTile();
				break;
			}
			case E_FloorItemToSpawn::FITS_destroyed:
			{
				if (currentFloorActor)
				{
					currentFloorActor->Destroy();
					currentFloorActor = nullptr;
				}

				if (currentItemActor)
				{
					currentItemActor->Destroy();
					currentItemActor = nullptr;
				}

				itemToSpawn = E_ItemToSpawn::ITS_destroyed;
				floorSelectionComp->SetVisibility(false);
				itemSelectionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 94.0f));

				break;
			}
			default:
			{
				if (currentFloorActor)
				{
					currentFloorActor->Destroy();
					currentFloorActor = nullptr;
				}

				floorSelectionComp->SetVisibility(true);
				break;
			}
		}
	}



	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_GridCell, rotateRight))
	{
		if (currentItemActor)
		{
			//float zRot = currentItemActor->GetActorRotation().Yaw;

			if (rotationVal == 0)
			{
				currentItemActor->SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));

				rotationVal = 1;
			}
			else if (rotationVal == 1)
			{
				currentItemActor->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
				rotationVal = 2;
			}
			else if (rotationVal == 2)
			{
				currentItemActor->SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
				rotationVal = 3;
			}
			else if (rotationVal == 3)
			{
				currentItemActor->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
				rotationVal = 0;
			}
		}

		rotateRight = false;
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_GridCell, rotateLeft))
	{
		if (currentItemActor)
		{
			if (rotationVal == 0)
			{
				currentItemActor->SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));

				rotationVal = 3;
			}
			else if (rotationVal == 1)
			{
				currentItemActor->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
				rotationVal = 0;
			}
			else if (rotationVal == 2)
			{
				currentItemActor->SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
				rotationVal = 1;
			}
			else if (rotationVal == 3)
			{
				currentItemActor->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
				rotationVal = 2;
			}
		}

		rotateLeft = false;
	}


	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif