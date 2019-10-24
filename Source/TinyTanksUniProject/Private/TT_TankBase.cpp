// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankBase.h"

// Sets default values
ATT_TankBase::ATT_TankBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATT_TankBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATT_TankBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATT_TankBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

