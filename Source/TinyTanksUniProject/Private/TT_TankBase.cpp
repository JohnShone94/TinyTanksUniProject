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

	moveSpeed = 2.0f;
	rotateSpeed = 1.25f;

	bIsDead = false;
	bIsStunned = false;
	maxHealthPoints = 2;
	currentHealthPoints = maxHealthPoints;
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

void ATT_TankBase::KillTank()
{
	if (!bIsDead)
	{
		bIsDead = true;
		currentHealthPoints = 0;
	}
}

void ATT_TankBase::StunTank()
{
	if (!bIsStunned)
		bIsStunned = true;
}

void ATT_TankBase::DamageTank()
{
	if (!bIsDead)
	{
		if (currentHealthPoints > 0)
			currentHealthPoints--;

		if (currentHealthPoints <= 0)
		{
			bIsDead = true;
			tankBaseMesh->SetVisibility(false);

			ATT_TankTurret* myTurret = Cast<ATT_TankTurret>(turretSlot->GetChildActor());
			if (myTurret)
				myTurret->GetTankGunBase()->SetVisibility(false);
		}
	}
}

