// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankSpawnPoint.h"

// Sets default values
ATT_TankSpawnPoint::ATT_TankSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATT_TankSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATT_TankSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

