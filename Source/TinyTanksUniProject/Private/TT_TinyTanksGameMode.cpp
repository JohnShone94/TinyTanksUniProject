// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TinyTanksGameMode.h"
#include "TT_TankBaseController.h"
#include "TT_TankTurretController.h"
#include "TT_TankBase.h"
#include "TT_TankTurret.h"
#include "TT_TankSpawnPoint.h"
#include "TT_BasicBullet.h"
#include "EngineUtils.h"
#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TT_MainCamera.h"

ATT_TinyTanksGameMode::ATT_TinyTanksGameMode()
{
	DefaultPawnClass = nullptr;

	bCanPlayersControlTanks = false;

	PlayerControllerClass = ATT_TankBaseController::StaticClass();
}

void ATT_TinyTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ATT_MainCamera> actorItr(GetWorld()); actorItr; ++actorItr)
	{
		mainCam = *actorItr;
	}
}

void ATT_TinyTanksGameMode::SpawnPlayerTanks()
{
	playersLeft = 0;
	for (TActorIterator<ATT_TankSpawnPoint> actorItr(GetWorld()); actorItr; ++actorItr)
	{
		ATT_TankSpawnPoint* actor = *actorItr;

		if (actor)
		{
			UWorld* const world = GetWorld();
			if (world != NULL)
			{
				ATT_TankBase* tank = actor->SpawnTank();
				if (tank)
				{
					tankArray.Add(tank);
					playersLeft++;

					UE_LOG(LogTemp, Warning, TEXT("GameMode(SpawnPlayerTanks): Successfully spawned a tank."));


					ATT_TankTurret* turret = Cast<ATT_TankTurret>(tank->GetTurretSlot()->GetChildActor());
					if (turret)
					{
						turretArray.Add(turret);
						UE_LOG(LogTemp, Warning, TEXT("GameMode(SpawnPlayerTanks): Successfully grabbed the turret."));
					}
					else
						UE_LOG(LogTemp, Error, TEXT("GameMode(SpawnPlayerTanks): Successfully spawned a tank but failed to grab the turret."));
				}
				else
					UE_LOG(LogTemp, Error, TEXT("GameMode(SpawnPlayerTanks): Failed to spawn a tank."));
			}
		}
	}
}

void ATT_TinyTanksGameMode::SpawnPlayerControllers()
{
	for (int i = GetNumPlayers(); i < ((tankArray.Num() * 2)); i++)
	{
		ATT_TankBaseController* playerCon = Cast<ATT_TankBaseController>(UGameplayStatics::CreatePlayer(GetWorld(), i, true));
		if (playerCon)
		{
			UE_LOG(LogTemp, Warning, TEXT("GameMode(SpawnPlayerControllers): Created a player controller, with Net ID: %d"), i);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("GameMode(SpawnPlayerControllers): Failed to create player controller with Net ID: %d"), i);
			continue;
		}
	}
}



void ATT_TinyTanksGameMode::AddPlayerConAtPosition(int i, ATT_TankBaseController* pController)
{
	switch (i)
	{
	case 0:
		playerMap.Add(1, pController);
		pController->AutoReceiveInput = EAutoReceiveInput::Player0;
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player One"), *pController->GetName());

		if (tankArray.Num() > 0)
		{
			pController->Possess(tankArray[0]);
			pController->SetTankPawn(tankArray[0]);
		}
		else
			UE_LOG(LogTemp, Error, TEXT("GameMode(AddPlayerConAtPosition): Failed to possess tank one."));

		break;

	case 1:
		playerMap.Add(2, pController);
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player Two"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player1;

		if (turretArray.Num() > 0)
		{
			pController->Possess(turretArray[0]);
			pController->SetTurretPawn(turretArray[0]);
		}
		else
			UE_LOG(LogTemp, Error, TEXT("GameMode(AddPlayerConAtPosition): Failed to possess tank one's turret."));

		break;

	case 2:
		playerMap.Add(3, pController);
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player Three"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player2;

		if (tankArray.Num() > 1)
		{
			pController->Possess(tankArray[1]);
			pController->SetTankPawn(tankArray[1]);
		}
		else
			UE_LOG(LogTemp, Error, TEXT("GameMode(AddPlayerConAtPosition): Failed to possess tank two."));

		break;

	case 3:
		playerMap.Add(4, pController);
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player Four"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player3;

		if (turretArray.Num() > 1)
		{
			pController->Possess(turretArray[1]);
			pController->SetTurretPawn(turretArray[1]);
		}
		else
			UE_LOG(LogTemp, Error, TEXT("GameMode(AddPlayerConAtPosition): Failed to possess tank two's turret."));

		break;
	case 4:
		playerMap.Add(5, pController);
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player Five"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player4;

		if (tankArray.Num() > 2)
		{
			pController->Possess(tankArray[2]);
			pController->SetTankPawn(tankArray[2]);
		}
		else
			UE_LOG(LogTemp, Error, TEXT("GameMode(AddPlayerConAtPosition): Failed to possess tank three."));

		break;
	case 5:
		playerMap.Add(6, pController);
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player Six"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player5;

		if (turretArray.Num() > 2)
		{
			pController->Possess(turretArray[2]);
			pController->SetTurretPawn(turretArray[2]);
		}
		else
			UE_LOG(LogTemp, Error, TEXT("GameMode(AddPlayerConAtPosition): Failed to possess tank three's turret."));

		break;
	case 6:
		playerMap.Add(7, pController);
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player Seven"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player6;

		if (tankArray.Num() > 3)
		{
			pController->Possess(tankArray[3]);
			pController->SetTankPawn(tankArray[3]);
		}
		else
			UE_LOG(LogTemp, Error, TEXT("GameMode(AddPlayerConAtPosition): Failed to possess tank four."));

		break;
	case 7:
		playerMap.Add(8, pController);
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player Eight"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player7;

		if (turretArray.Num() > 3)
		{
			pController->Possess(turretArray[3]);
			pController->SetTurretPawn(turretArray[3]);
		}
		else
			UE_LOG(LogTemp, Error, TEXT("GameMode(AddPlayerConAtPosition): Failed to possess tank four's turret."));

		break;

	default:
		break;
	}
}

void ATT_TinyTanksGameMode::ResetPlayers()
{
	if (playerArray.Num() > 0)
	{
		for (int i = 0; i < playerArray.Num(); i++)
		{
			playerArray[i]->AutoReceiveInput = EAutoReceiveInput::Disabled;
			playerArray[i]->UnPossess();
			playerArray[i]->SetTankPawn(nullptr);
			playerArray[i]->SetTurretPawn(nullptr);
		}
	}

	if (tankArray.Num() > 0)
	{
		for (int i = 0; i < tankArray.Num(); i++)
		{
			tankArray[i]->Destroy();
		}

		tankArray.Empty();
		turretArray.Empty();
	}
	else
	{
		for (TActorIterator<ATT_TankBase> actorItr(GetWorld()); actorItr; ++actorItr)
		{
			ATT_TankBase* actor = *actorItr;

			if (actor)
			{
				actor->Destroy();
			}
		}
		tankArray.Empty();
		turretArray.Empty();
	}

	for (TActorIterator<ATT_BasicBullet> actorItr(GetWorld()); actorItr; ++actorItr)
	{
		ATT_BasicBullet* actor = *actorItr;

		if (actor)
		{
			actor->Destroy();
		}
	}
}

void ATT_TinyTanksGameMode::SetupPlayerControllers(bool bOverride)
{
	if (playerArray.Num() <= 0 || bOverride)
	{
		playerArray.Empty();
		for (TActorIterator<ATT_TankBaseController> actorItr(GetWorld()); actorItr; ++actorItr)
		{
			ATT_TankBaseController* actor = *actorItr;
			if (actor)
			{
				playerArray.Add(actor);
			}
		}
	}

	if (playerArray.Num() > 0)
	{
		for (int i = 0; i < playerArray.Num(); i++)
		{
			AddPlayerConAtPosition(i, playerArray[i]);
		}
	}
}

ATT_TankBaseController* ATT_TinyTanksGameMode::GetPlayerConAtPosition(int32 i)
{
	if ((playerMap.Num() > 0) && (playerMap.Contains(i)))
		return *playerMap.Find(i);
	else
		return nullptr;
}

int32 ATT_TinyTanksGameMode::GetPlayerPositionFromCon(ATT_TankBaseController* con)
{
	if ((playerMap.Num() > 0) && (playerMap.FindKey(con)))
		return *playerMap.FindKey(con);
	else
		return 0;
}

void ATT_TinyTanksGameMode::RemoveTank()
{
	playersLeft = (playersLeft - 1);

	if (playersLeft <= 1)
		mainCam->LastManIsStanding();
}

void ATT_TinyTanksGameMode::AddTankToGM(ATT_TankBase * tank)
{
	//if (!tankOne)
	//{		
	//	tankOne = tank;
	//	turretOne = Cast<ATT_TankTurret>(tank->GetTurretSlot()->GetChildActor());
	//}
	//else if (!tankTwo)
	//{
	//	tankTwo = tank;
	//	turretTwo = Cast<ATT_TankTurret>(tank->GetTurretSlot()->GetChildActor());
	//}
	//else
	//	UE_LOG(LogTemp, Warning, TEXT("ALL TANK POSITIONS ARE NOW FULL"));

	//if (tankOne)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("TANK POSITION 1: %s"), *tankOne->GetName());
	//	
	//	if(turretOne)
	//		UE_LOG(LogTemp, Warning, TEXT("TURRET POSITION 1: %s"), *turretOne->GetName());
	//}
	//if (tankTwo)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("TANK POSITION 2: %s"), *tankTwo->GetName());
	//	
	//	if(turretTwo)
	//		UE_LOG(LogTemp, Warning, TEXT("TURRET POSITION 2: %s"), *turretTwo->GetName());
	//}
}
