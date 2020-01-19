// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/CollisionProfile.h"
#include "TT_BasicBullet.h"
#include "Engine.h"

ATT_TankTurret::ATT_TankTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	tankGunBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Gun Base"));
	tankGunBase->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	RootComponent = tankGunBase;

	UStaticMesh* meshToUse = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("StaticMesh'/Game/Assets/Tank/Aztank1_tanktop.Aztank1_tanktop'")));
	UMaterial* materialToUse = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("Material'/Game/Blueprints/Red.Red'")));
	if (meshToUse)
		tankGunBase->SetStaticMesh(meshToUse);
	if (materialToUse)
		tankGunBase->GetStaticMesh()->SetMaterial(0, materialToUse);

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
	gunOffset = FVector(60.0f, 0.0f, 0.0f);
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



