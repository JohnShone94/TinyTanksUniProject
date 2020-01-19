// Fill out your copyright notice in the Description page of Project Settings.

#include "TT_Powerup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "TT_TankBase.h"
#include "Engine.h"

// Sets default values
ATT_Powerup::ATT_Powerup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	powerupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Powerup Mesh"));
	RootComponent = powerupMesh;

	powerupOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Powerup Overlap Component"));
	powerupOverlap->SetupAttachment(RootComponent);


	pitchValue = 0.0f;
	yawValue = 0.0f;
	rollValue = 0.0f;

}

// Called when the game starts or when spawned
void ATT_Powerup::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ATT_Powerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rot = FRotator(pitchValue, yawValue, rollValue);

	FQuat quat = FQuat(rot);

	AddActorLocalRotation(quat, false, 0, ETeleportType::None);
}