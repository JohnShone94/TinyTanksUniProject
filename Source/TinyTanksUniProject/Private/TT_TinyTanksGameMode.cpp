// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TinyTanksGameMode.h"
#include "TT_TankBaseController.h"
#include "TT_TankTurretController.h"

void ATT_TinyTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnPlayerControllerCommon(ENetRole::ROLE_None, FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator, ATT_TankBaseController::StaticClass());
	SpawnPlayerControllerCommon(ENetRole::ROLE_None, FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator, ATT_TankTurretController::StaticClass());

}