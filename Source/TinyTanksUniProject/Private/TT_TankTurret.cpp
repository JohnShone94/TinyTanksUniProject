// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine.h"

ATT_TankTurret::ATT_TankTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	tankGunBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Gun Base"));
	tankGunBase->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	RootComponent = tankGunBase;

	fireLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Fire Location"));
	fireLocation->SetupAttachment(RootComponent);

	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = nullptr;

	rotateSpeed = 3.0f;
	fireRate = 1.25f;
}

void ATT_TankTurret::BeginPlay()
{
	Super::BeginPlay();
	
	turretForwardVector = tankGunBase->GetForwardVector();
}

void ATT_TankTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ATT_TankTurret::GetForwardVector()
{
	//UE_LOG(LogTemp, Error, TEXT("FORWARDVECTOR %s"), *tankGunBase->GetForwardVector().ToString());
	turretForwardVector = tankGunBase->GetForwardVector();
	return turretForwardVector;
}



