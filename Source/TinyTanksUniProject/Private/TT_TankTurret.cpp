// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/CollisionProfile.h"
#include "TT_BasicBullet.h"
#include "Engine.h"


// Sets default values
ATT_TankTurret::ATT_TankTurret()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UStaticMesh* meshToUse = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("StaticMesh'/Game/Assets/Tank/Tank_1_polySurface26.Tank_1_polySurface26'")));
	UMaterial* materialToUse = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("Material'/Game/Blueprints/Red.Red'")));

	tankGunBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Gun Base"));
	tankGunBase->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	if (meshToUse)
		tankGunBase->SetStaticMesh(meshToUse);

	if (materialToUse)
		tankGunBase->GetStaticMesh()->SetMaterial(0, materialToUse);


	RootComponent = tankGunBase;

	fireLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Fire Location"));
	fireLocation->SetupAttachment(RootComponent);

	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = nullptr;

	rotateSpeed = 2.0f;
	fireRate = 1.0f;
}

// Called when the game starts or when spawned
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
	turretForwardVector = tankGunBase->GetForwardVector();

	UE_LOG(LogTemp, Error, TEXT("FORWARDVECTOR %s"), *tankGunBase->GetForwardVector().ToString());

	return turretForwardVector;
}



