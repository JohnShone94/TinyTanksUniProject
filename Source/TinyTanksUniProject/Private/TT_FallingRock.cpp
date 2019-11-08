// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_FallingRock.h"

// Sets default values
ATT_FallingRock::ATT_FallingRock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATT_FallingRock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATT_FallingRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

