// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TinyTanksGameMode.h"
#include "TT_TankBaseController.h"
#include "TT_TankTurretController.h"
#include "TT_TankBase.h"
#include "TT_TankTurret.h"
#include "EngineUtils.h"
#include "ConstructorHelpers.h"

ATT_TinyTanksGameMode::ATT_TinyTanksGameMode()
{
	DefaultPawnClass = nullptr;

	PlayerControllerClass = ATT_TankBaseController::StaticClass();
}

void ATT_TinyTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!tankOne || !tankTwo)
	{
		for (TActorIterator<ATT_TankBase> actorItr(GetWorld()); actorItr; ++actorItr)
		{

			ATT_TankBase *actor = *actorItr;

			if (!tankOne)
				tankOne = actor;
			else if (!tankTwo)
				tankTwo = actor;
			else
				UE_LOG(LogTemp, Warning, TEXT("ALL TANK POSITIONS ARE NOW FULL"));

			if (tankOne)
				UE_LOG(LogTemp, Warning, TEXT("TANK POSITIONS 1: %s"), *tankOne->GetName());
			if (tankTwo)
				UE_LOG(LogTemp, Warning, TEXT("TANK POSITIONS 2: %s"), *tankTwo->GetName());
		}
	}

	SpawnPlayerControllerCommon(ENetRole::ROLE_None, FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator, PlayerControllerClass);
	SpawnPlayerControllerCommon(ENetRole::ROLE_None, FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator, PlayerControllerClass);
	SpawnPlayerControllerCommon(ENetRole::ROLE_None, FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator, PlayerControllerClass);
}


void ATT_TinyTanksGameMode::AddPlayerConAtPosition(int i, ATT_TankBaseController* pController)
{
	switch (i)
	{
	case 1:
		playerMap.Add(1, pController);
		UE_LOG(LogTemp, Warning, TEXT("Added %s to Player One"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player0;

		if(tankOne)
			pController->Possess(tankOne);
		else
			UE_LOG(LogTemp, Error, TEXT("FAILED TO POSSESS TANK ONE"));

		break;

	case 2:
		playerMap.Add(2, pController);
		UE_LOG(LogTemp, Warning, TEXT("Added %s to Player Two"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player1;

		if (tankOne)
		{
			ATT_TankTurret* turret = Cast<ATT_TankTurret>(tankOne->GetTurretSlot());
			pController->Possess(turret);
		}
		else
			UE_LOG(LogTemp, Error, TEXT("FAILED TO POSSESS TANK ONE'S TURRET"));

		break;

	case 3:
		playerMap.Add(3, pController);
		UE_LOG(LogTemp, Warning, TEXT("Added %s to Player Three"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player2;

		if(tankTwo)
			pController->Possess(tankTwo);
		else
			UE_LOG(LogTemp, Error, TEXT("FAILED TO POSSESS TANK TWO"));

		break;

	case 4:
		playerMap.Add(4, pController);
		UE_LOG(LogTemp, Warning, TEXT("Added %s to Player Four"), *pController->GetName());
		pController->AutoReceiveInput = EAutoReceiveInput::Player3;

		if (tankTwo)
		{
			ATT_TankTurret* turret = Cast<ATT_TankTurret>(tankTwo->GetTurretSlot());
			pController->Possess(turret);
		}
		else
			UE_LOG(LogTemp, Error, TEXT("FAILED TO POSSESS TANK TWO'S TURRET"));

		break;

	default:
		break;
	}
}

ATT_TankBaseController* ATT_TinyTanksGameMode::GetPlayerConAtPosition(int32 i)
{
	if (playerMap.Contains(i))
		return *playerMap.Find(i);
	else
		return nullptr;
}

int32 ATT_TinyTanksGameMode::GetPlayerPositionFromCon(ATT_TankBaseController* con)
{
	if (playerMap.FindKey(con))
		return *playerMap.FindKey(con);
	else
		return 0;
}

void ATT_TinyTanksGameMode::AddTankToGM(ATT_TankBase * tank)
{
	if(!tankOne)
		tankOne = tank;
	else if(!tankTwo)
		tankTwo = tank;
	else
		UE_LOG(LogTemp, Warning, TEXT("ALL TANK POSITIONS ARE NOW FULL"));

	if(tankOne)
		UE_LOG(LogTemp, Warning, TEXT("TANK POSITIONS 1: %s"), *tankOne->GetName());
	if (tankTwo)
		UE_LOG(LogTemp, Warning, TEXT("TANK POSITIONS 2: %s"), *tankTwo->GetName());
}
