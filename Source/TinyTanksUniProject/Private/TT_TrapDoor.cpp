// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TrapDoor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATT_TrapDoor::ATT_TrapDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	trapDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trap Door Mesh"));
	trapDoorMesh->SetRelativeScale3D(FVector(0.465f, 0.465f, 0.3f));
	RootComponent = trapDoorMesh;

}

// Called when the game starts or when spawned
void ATT_TrapDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATT_TrapDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

