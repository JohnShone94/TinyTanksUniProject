// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_DestructableWall.h"

// Sets default values
ATT_DestructableWall::ATT_DestructableWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATT_DestructableWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATT_DestructableWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

