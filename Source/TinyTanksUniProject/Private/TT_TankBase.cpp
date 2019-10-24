// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankBase.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "TT_TankTurret.h"

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

	moveSpeed = 10.0f;
}

// Called when the game starts or when spawned
void ATT_TankBase::BeginPlay()
{
	Super::BeginPlay();
	
	tankForwardVector = tankBaseMesh->GetForwardVector();

}

// Called every frame
void ATT_TankBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

