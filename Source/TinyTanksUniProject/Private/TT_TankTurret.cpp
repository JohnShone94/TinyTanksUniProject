// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"

// Sets default values
ATT_TankTurret::ATT_TankTurret()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	tankGunBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Gun Base"));
	tankGunBase->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	tankGunBarrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Gun Barrel"));
	tankGunBarrel->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	RootComponent = tankGunBase;
	tankGunBarrel->SetupAttachment(RootComponent);

	rotateSpeed = 10.0f;
	gunOffset = FVector(90.f, 0.f, 0.f);
	fireRate = 0.1f;
}

// Called when the game starts or when spawned
void ATT_TankTurret::BeginPlay()
{
	Super::BeginPlay();
	
	turretForwardVector = tankGunBarrel->GetForwardVector();
}

// Called every frame
void ATT_TankTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


