// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankBase.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "TT_TankTurret.h"
#include "TT_TinyTanksGameMode.h"
#include "TT_BasicBullet.h"

// Sets default values
ATT_TankBase::ATT_TankBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	tankBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Body"));
	tankBaseMesh->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	tankBaseMesh->SetSimulatePhysics(true);
	tankBaseMesh->bIgnoreRadialForce = true;
	tankBaseMesh->bIgnoreRadialImpulse = true;
	tankBaseMesh->SetEnableGravity(false);
	RootComponent = tankBaseMesh;


	turretSlot = CreateDefaultSubobject<UChildActorComponent>(TEXT("Turret Slot"));
	turretSlot->SetChildActorClass(ATT_TankTurret::StaticClass());
	turretSlot->SetupAttachment(RootComponent);

	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = nullptr;

	moveSpeed = 10.0f;
	rotateSpeed = 10.0f;
}

// Called when the game starts or when spawned
void ATT_TankBase::BeginPlay()
{
	Super::BeginPlay();

	ATT_TinyTanksGameMode* gameMode = Cast<ATT_TinyTanksGameMode>(GetWorld()->GetAuthGameMode());
	gameMode->AddTankToGM(this);
}

// Called every frame
void ATT_TankBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

