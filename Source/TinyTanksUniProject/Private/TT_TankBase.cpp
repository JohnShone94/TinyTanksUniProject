// Fill out your copyright notice in the Description page of Project Settings.

#include "TT_TankBase.h"
#include "TT_Powerup.h"
#include "TT_TankTurret.h"
#include "TT_MagicMissile.h"
#include "TT_SpringBoard.h"
#include "TT_PressurePlate.h"
#include "TT_TinyTanksGameMode.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Math/InterpCurve.h"
#include "Math/UnrealMathUtility.h"

ATT_TankBase::ATT_TankBase()
{
	PrimaryActorTick.bCanEverTick = true;

	tankBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Body"));
	RootComponent = tankBaseMesh;

	shildMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shild Mesh"));
	shildMesh->SetVisibility(false);
	shildMesh->SetupAttachment(RootComponent);

	tankOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Tank Base Overlap"));
	tankOverlap->SetupAttachment(RootComponent);

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

	currentLocation = GetActorLocation();

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

void ATT_TankBase::SetTankTeam(ESelectedTeam team)
{
	tankTeam = team;
	UpdateTankTeam();
}

void ATT_TankBase::UpdateTankTeam_Implementation()
{
}

void ATT_TankBase::KillTank()
{
	if (!bIsDead)
	{
		bIsDead = true;
		currentHealthPoints = 0;
		gameMode->RemoveTank(this);
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
		ATT_SpringBoard* spring = Cast<ATT_SpringBoard>(OtherActor);
		if (spring)
		{
			setLocation = spring->newActorLocation;
			setLocation.Z = 125.0f;
			SetActorLocation(FMath::InterpEaseIn(currentLocation, setLocation, 1, 125));
		}

		ATT_Powerup* powerup = Cast<ATT_Powerup>(OtherActor);
		if (powerup)			
		{
			switch (powerup->GetPowerupType())
			{
				case EPowerupType::PT_fastBullet:
				{
					if (currentOffensivePowerup == EPowerupType::PT_none)
					{
						powerup->Destroy();
						currentOffensivePowerup = EPowerupType::PT_fastBullet;
					}

					break;
				}
				case EPowerupType::PT_missileBullet:
				{
					if (currentOffensivePowerup == EPowerupType::PT_none)
					{
						powerup->Destroy();
						currentOffensivePowerup = EPowerupType::PT_missileBullet;
					}

					break;
				}
				case EPowerupType::PT_undergroundBullet:
				{
					if (currentOffensivePowerup == EPowerupType::PT_none)
					{
						powerup->Destroy();
						currentOffensivePowerup = EPowerupType::PT_undergroundBullet;
					}

					break;
				}
				case EPowerupType::PT_stunBullet:
				{
					if (currentOffensivePowerup == EPowerupType::PT_none)
					{
						powerup->Destroy();
						currentOffensivePowerup = EPowerupType::PT_stunBullet;
					}

					break;
				}
				case EPowerupType::PT_airblast:
				{
					if (currentDeffensivePowerup == EPowerupType::PT_none)
					{
						powerup->Destroy();
						currentDeffensivePowerup = EPowerupType::PT_airblast;
					}

					break;
				}
				case EPowerupType::PT_smokeScreen:
				{
					if (currentDeffensivePowerup == EPowerupType::PT_none)
					{
						powerup->Destroy();
						currentDeffensivePowerup = EPowerupType::PT_smokeScreen;
					}

					break;
				}
				case EPowerupType::PT_shild:
				{
					if (currentDeffensivePowerup == EPowerupType::PT_none)
					{
						powerup->Destroy();
						currentDeffensivePowerup = EPowerupType::PT_shild;
					}

					break;
				}
				case EPowerupType::PT_floating:
				{
					if (currentDeffensivePowerup == EPowerupType::PT_none)
					{
						powerup->Destroy();
						currentDeffensivePowerup = EPowerupType::PT_floating;
					}

					break;
				}
				case EPowerupType::PT_none:
				{
					break;
				}
				case EPowerupType::PT_speedBoost:
				{
					//apply temp speedboost
					break;
				}
				default:
				{
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
			gameMode->RemoveTank(this);
			TankHasDied();

			tankBaseMesh->SetVisibility(true);

			ATT_TankTurret* myTurret = Cast<ATT_TankTurret>(turretSlot->GetChildActor());
			if (myTurret)
				myTurret->GetTankGunBase()->SetVisibility(true);
		}
	}
}

void ATT_TankBase::ResetDeffensivePowerup()
{
	currentDeffensivePowerup = EPowerupType::PT_none;
}

void ATT_TankBase::ResetOffensivePowerup()
{
	currentOffensivePowerup = EPowerupType::PT_none;
}

void ATT_TankBase::ActivateShild(bool val)
{
	shildMesh->SetVisibility(val);
	bIsShilded = val;
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