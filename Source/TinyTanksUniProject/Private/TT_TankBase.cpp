// Fill out your copyright notice in the Description page of Project Settings.

#include "TT_TankBase.h"
#include "TT_Powerup.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine.h"
#include "TT_TankTurret.h"
#include "TT_TinyTanksGameMode.h"
#include "TT_BasicBullet.h"

ATT_TankBase::ATT_TankBase()
{
	PrimaryActorTick.bCanEverTick = true;

	tankBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Body"));
	tankBaseMesh->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	tankBaseMesh->SetSimulatePhysics(true);
	tankBaseMesh->bIgnoreRadialForce = true;
	tankBaseMesh->bIgnoreRadialImpulse = true;
	tankBaseMesh->SetEnableGravity(false);
	RootComponent = tankBaseMesh;

	tankOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Tank Base Overlap"));
	tankOverlap->SetCollisionProfileName("OverlapAll");
	tankOverlap->SetSimulatePhysics(false);
	tankOverlap->SetEnableGravity(false);
	tankOverlap->SetupAttachment(RootComponent);

	UStaticMesh* meshToUse = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("StaticMesh'/Game/Assets/Tank/Tank_1_polySurface59.Tank_1_polySurface59'")));
	UMaterial* materialToUse = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("Material'/Game/Blueprints/Green.Green'")));
	if (meshToUse)
		tankBaseMesh->SetStaticMesh(meshToUse);
	if (materialToUse)
		tankBaseMesh->SetMaterial(0, materialToUse);

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

	stunTimer = 2.0f;
}

void ATT_TankBase::BeginPlay()
{
	Super::BeginPlay();

	tankOverlap->OnComponentBeginOverlap.AddDynamic(this, &ATT_TankBase::OnOverlapBegin);

	gameMode = Cast<ATT_TinyTanksGameMode>(GetWorld()->GetAuthGameMode());
}

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
		gameMode->RemoveTank();
		TankHasDied();
	}
}

void ATT_TankBase::StunTank()
{
	if (!bIsStunned)
		bIsStunned = true;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_StunTimerExpired, this, &ATT_TankBase::StunTimerExpired, stunTimer);
}

void ATT_TankBase::StunTimerExpired()
{
	bIsStunned = false;
}

void ATT_TankBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ATT_Powerup* powerup = Cast<ATT_Powerup>(OtherActor);
		if (powerup)			
		{	
			switch (powerup->GetPowerupType())
			{
				case EPowerupType::PT_fastBullet:
				{
//					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("fast Pickup"));

					currentPowerup = EPowerupType::PT_fastBullet;

					break;
				}
				case EPowerupType::PT_missile:
				{
//					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT(" Missile Pickup"));
					currentPowerup = EPowerupType::PT_missile;
					break;
				}
				case EPowerupType::PT_undergroundBullet:
				{

					currentPowerup = EPowerupType::PT_undergroundBullet;
					break;
				}
				case EPowerupType::PT_wallBullet:
				{
					currentPowerup = EPowerupType::PT_wallBullet;
					break;
				}
				case EPowerupType::PT_speedBoost:
				{
					currentPowerup = EPowerupType::PT_speedBoost;
					break;
				}
				case EPowerupType::PT_none:
				{
//					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("none"));

					break;
				}
				default:
				{
//					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Defult"));
					break;
				}
			}
		}
	}
}

void ATT_TankBase::DamageTank()
{
	if (!bIsDead)
	{
		if (currentHealthPoints > 0)
		{
			TankHasBeenDamaged();
			currentHealthPoints--;
		}

		if (currentHealthPoints <= 0)
		{
			bIsDead = true;
			gameMode->RemoveTank();
			TankHasDied();

			tankBaseMesh->SetVisibility(true);

			ATT_TankTurret* myTurret = Cast<ATT_TankTurret>(turretSlot->GetChildActor());
			if (myTurret)
				myTurret->GetTankGunBase()->SetVisibility(true);
		}
	}
}

void ATT_TankBase::ResetPowerup()
{

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Reset to defult"));
	currentPowerup = EPowerupType::PT_none;
}

void ATT_TankBase::TankHasDied_Implementation()
{
}

void ATT_TankBase::TankHasBeenDamaged_Implementation()
{
}

void ATT_TankBase::TankHasFired_Implementation()
{
}