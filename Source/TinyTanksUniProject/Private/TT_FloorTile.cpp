// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_FloorTile.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ATT_FloorTile::ATT_FloorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	tileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile Mesh"));
	tileMesh->SetRelativeScale3D(FVector(0.465f, 0.465f, 0.05f));
	RootComponent = tileMesh;
}

// Called when the game starts or when spawned
void ATT_FloorTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATT_FloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

