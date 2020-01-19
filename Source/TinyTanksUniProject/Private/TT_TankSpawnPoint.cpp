// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankSpawnPoint.h"
#include "TT_TankBase.h"
#include "Engine.h"
#include "EngineUtils.h"
#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ATT_TankSpawnPoint::ATT_TankSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;

}

ATT_TankBase* ATT_TankSpawnPoint::SpawnTank()
{
	FActorSpawnParameters SpawnParams;
	ATT_TankBase* actorRef = GetWorld()->SpawnActor<ATT_TankBase>(tanktospawn, GetTransform(), SpawnParams);
	return actorRef;
}

void ATT_TankSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATT_TankSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

