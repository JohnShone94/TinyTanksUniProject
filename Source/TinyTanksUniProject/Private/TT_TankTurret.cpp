// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankTurret.h"

// Sets default values
ATT_TankTurret::ATT_TankTurret()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATT_TankTurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATT_TankTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATT_TankTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

