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

	overlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap Sphere"));
	overlapSphere->SetupAttachment(RootComponent);

	fireLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Fire Location"));
	fireLocation->SetupAttachment(RootComponent);

	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = nullptr;

	rotateSpeed = 3.0f;
	fireRate = 1.25f;
}

void ATT_TankTurret::SetTurretTeam(ESelectedTeam team)
{
	turretTeam = team;
	UpdateTankTeam();
}

void ATT_TankTurret::UpdateTankTeam_Implementation()
{
}

void ATT_TankTurret::BeginPlay()
{
	Super::BeginPlay();
	
	turretForwardVector = tankGunBase->GetForwardVector();

	turretCurrentRotation = GetActorRotation();

	overlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ATT_TankTurret::OnOverlapBegin);
}

void ATT_TankTurret::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		isOverlapped = true;
	}
	else
	{
		isOverlapped = false;
	}
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



