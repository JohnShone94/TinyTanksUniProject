// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_StandardWall.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ATT_StandardWall::ATT_StandardWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	wallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Mesh"));
	RootComponent = wallMesh;

}

// Called when the game starts or when spawned
void ATT_StandardWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATT_StandardWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

