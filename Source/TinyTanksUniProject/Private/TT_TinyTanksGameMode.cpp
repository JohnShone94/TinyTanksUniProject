// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TinyTanksGameMode.h"
#include "TT_TankBaseController.h"
#include "TT_TankBase.h"
#include "TT_TankTurret.h"
#include "TT_TankSpawnPoint.h"
#include "TT_MagicMissile.h"

#include "Engine.h"
#include "EngineUtils.h"
#include "Engine/LocalPlayer.h"
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

	UWorld* const world = GetWorld();
	if (world != NULL)
	{
		for (TActorIterator<ATT_MainCamera> actorItr(world); actorItr; ++actorItr)
		{
			mainCam = *actorItr;
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

void ATT_TinyTanksGameMode::RemoveTank(ATT_TankBase* tank, bool addWin)
{
	if (tank && addWin)
	{
		if (tank->GetTankTeam() == ESelectedTeam::ST_teamOneBase)
			teamTwoScore++;

		if (tank->GetTankTeam() == ESelectedTeam::ST_teamTwoBase)
			teamOneScore++;
	}

	playersLeft = (playersLeft - 1);

	if (playersLeft <= 1 && mainCam)
		mainCam->LastManIsStanding();
}

void ATT_TinyTanksGameMode::AddPlayerConAtPosition(int i, ATT_TankBaseController* pController)
{
	switch (i)
	{
	case 0:
		playerMap.Add(1, pController);
		pController->AutoReceiveInput = EAutoReceiveInput::Player0;
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player One"), *pController->GetName());

		break;

	case 1:
		playerMap.Add(2, pController);
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player Two"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player1;

		break;

	case 2:
		playerMap.Add(3, pController);
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player Three"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player2;
		break;

	case 3:
		playerMap.Add(4, pController);
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player Four"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player3;
		break;
	case 4:
		playerMap.Add(5, pController);
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player Five"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player4;
		break;
	case 5:
		playerMap.Add(6, pController);
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player Six"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player5;
		break;
	case 6:
		playerMap.Add(7, pController);
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player Seven"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player6;
		break;
	case 7:
		playerMap.Add(8, pController);
		UE_LOG(LogTemp, Warning, TEXT("GameMode(AddPlayerConAtPosition): Added %s to Player Eight"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player7;
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
			playerArray[i]->AcknowledgedPawn = nullptr;
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

	for (TActorIterator<ATT_MagicMissile> actorItr(GetWorld()); actorItr; ++actorItr)
	{
		ATT_MagicMissile* actor = *actorItr;

		if (actor)
		{
			actor->Destroy();
		}
	}
}

void ATT_TinyTanksGameMode::SpawnPlayerControllers()
{
	UWorld* const world = GetWorld();
	if (world != NULL)
	{
		for (int i = GetNumPlayers(); i < ((tankArray.Num() * 2)); i++)
		{
			TSubclassOf<ATT_TankBaseController> con;

			ATT_TankBaseController* playerCon = Cast<ATT_TankBaseController>(SpawnPlayerControllerCommon(ENetRole::ROLE_MAX, FVector::ZeroVector, FRotator::ZeroRotator, ATT_TankBaseController::StaticClass()));
			if (playerCon)
			{
				playerCon->NetPlayerIndex = i;
				playerCon->SetAsLocalPlayerController();
				FString error;
				ULocalPlayer* localPlayer = GetWorld()->GetGameInstance()->CreateLocalPlayer(i, error, false);
				if (localPlayer)
				{
					playerCon->SetPlayer(localPlayer);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("GameMode(SpawnPlayerControllers): %s"), *error);
				}


				UE_LOG(LogTemp, Warning, TEXT("GameMode(SpawnPlayerControllers): Created a player controller, with Net ID: %d"), playerCon->NetPlayerIndex);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("GameMode(SpawnPlayerControllers): Failed to create player controller with Net ID: %d"), i);
				continue;
			}
		}

		SetupPlayerControllers(true);
	}

}


void ATT_TinyTanksGameMode::SpawnPlayerTanks()
{
	UWorld* const world = GetWorld();
	if (world != NULL)
	{
		playersLeft = 0;
		for (TActorIterator<ATT_TankSpawnPoint> actorItr(world); actorItr; ++actorItr)
		{
			ATT_TankSpawnPoint* actor = *actorItr;

			if (actor)
			{
				ATT_TankBase* tank = actor->SpawnTank();
				if (tank)
				{
					playersLeft++;
					tankArray.Add(tank);

					UE_LOG(LogTemp, Warning, TEXT("GameMode(SpawnPlayerTanks): Successfully spawned a tank."));


					ATT_TankTurret* turret = Cast<ATT_TankTurret>(tank->GetAttachedTurret());
					if (turret)
					{
						turretArray.Add(turret);
						UE_LOG(LogTemp, Warning, TEXT("GameMode(SpawnPlayerTanks): Successfully grabbed the turret."));

						switch (playersLeft)
						{
						case 1:
						{
							tank->SetTankTeam(ESelectedTeam::ST_teamOneBase);
							turret->SetTurretTeam(ESelectedTeam::ST_teamOneTurret);
							break;
						}
						case 2:
						{
							tank->SetTankTeam(ESelectedTeam::ST_teamTwoBase);
							turret->SetTurretTeam(ESelectedTeam::ST_teamTwoTurret);
							break;
						}
						default:
							break;
						}

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

			switch (i)
			{
			case 0:
			{
				playerArray[i]->SetPlayerTeam(ESelectedTeam::ST_teamOneBase);
				break;
			}
			case 1:
			{
				playerArray[i]->SetPlayerTeam(ESelectedTeam::ST_teamOneTurret);
				break;
			}
			case 2:
			{
				playerArray[i]->SetPlayerTeam(ESelectedTeam::ST_teamTwoBase);
				break;
			}
			case 3:
			{
				playerArray[i]->SetPlayerTeam(ESelectedTeam::ST_teamTwoTurret);
				break;
			}
			default:
				break;
			}
		}
	}
}

void ATT_TinyTanksGameMode::PlayerPossessTank()
{
	if (playerArray.Num() >= 4)
	{
		for (int i = 0; i < playerArray.Num(); i++)
		{
			ATT_TankBaseController* con = playerArray[i];
			if (con)
			{
				ESelectedTeam team = con->GetPlayerTeam();

				switch (team)
				{
				case ESelectedTeam::ST_none:
				{
					UE_LOG(LogTemp, Warning, TEXT("GameMode(PlayerPossessTank): %s failed to possess anything as it has no team selected."), *con->GetName());
					break;
				}
				case ESelectedTeam::ST_teamOneBase:
				{
					if (tankArray.Num() > 0)
					{
						for (int p = 0; p < tankArray.Num(); p++)
						{
							if (tankArray[p]->GetTankTeam() == ESelectedTeam::ST_teamOneBase)
							{
								con->Possess(tankArray[p]);
								con->AcknowledgePossession(tankArray[p]);
								con->SetTankPawn(tankArray[p]);

								UE_LOG(LogTemp, Warning, TEXT("GameMode(PlayerPossessTank): %s possessed Blue Team Base"), *con->GetName());
							}
						}
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("GameMode(PlayerPossessTank): %s failed to possess Blue Team Base"), *con->GetName());
					}

					break;
				}
				case ESelectedTeam::ST_teamOneTurret:
				{
					if (turretArray.Num() > 0)
					{
						for (int p = 0; p < turretArray.Num(); p++)
						{
							if (turretArray[p]->GetTurretTeam() == ESelectedTeam::ST_teamOneTurret)
							{
								con->Possess(turretArray[p]);
								con->AcknowledgePossession(turretArray[p]);
								con->SetTurretPawn(turretArray[p]);

								UE_LOG(LogTemp, Warning, TEXT("GameMode(PlayerPossessTank): %s possessed Blue Team Turret"), *con->GetName());
							}
						}
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("GameMode(PlayerPossessTank): %s failed to possess Blue Team Turret"), *con->GetName());
					}

					break;
				}
				case ESelectedTeam::ST_teamTwoBase:
				{
					if (tankArray.Num() > 0)
					{
						for (int p = 0; p < tankArray.Num(); p++)
						{
							if (tankArray[p]->GetTankTeam() == ESelectedTeam::ST_teamTwoBase)
							{
								con->Possess(tankArray[p]);
								con->AcknowledgePossession(tankArray[p]);
								con->SetTankPawn(tankArray[p]);

								UE_LOG(LogTemp, Warning, TEXT("GameMode(PlayerPossessTank): %s possessed Green Team Base"), *con->GetName());
							}
						}
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("GameMode(PlayerPossessTank): %s failed to possess Green Team Base"), *con->GetName());
					}

					break;
				}
				case ESelectedTeam::ST_teamTwoTurret:
				{
					if (turretArray.Num() > 0)
					{
						for (int p = 0; p < turretArray.Num(); p++)
						{
							if (turretArray[p]->GetTurretTeam() == ESelectedTeam::ST_teamTwoTurret)
							{
								con->Possess(turretArray[p]);
								con->AcknowledgePossession(turretArray[p]);
								con->SetTurretPawn(turretArray[p]);

								UE_LOG(LogTemp, Warning, TEXT("GameMode(PlayerPossessTank): %s possessed Green Team Turret"), *con->GetName());
							}
						}
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("GameMode(PlayerPossessTank): %s failed to possess Green Team Turret"), *con->GetName());
					}

					break;
				}
				default:
					break;
				}
			}
		}
	}
}
