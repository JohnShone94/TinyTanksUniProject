// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_Missile.h"

// Sets default values
ATT_Missile::ATT_Missile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATT_Missile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATT_Missile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

