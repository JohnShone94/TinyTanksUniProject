// Fill out your copyright notice in the Description page of Project Settings.

#include "TT_TankBase.h"
#include "TT_Powerup.h"
#include "TT_TankTurret.h"
#include "TT_MagicMissile.h"
#include "TT_SpringBoard.h"
#include "TT_PressurePlate.h"
#include "TT_TinyTanksGameMode.h"
#include "TT_PowerupHolder.h"

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

	tankOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Tank Base Overlap"));
	tankOverlap->SetupAttachment(RootComponent);

	turretSlot = CreateDefaultSubobject<UChildActorComponent>(TEXT("Turret Slot"));
	turretSlot->SetupAttachment(RootComponent);

	powerupHolder = CreateDefaultSubobject<UChildActorComponent>(TEXT("Powerhup Holder Slot"));
	powerupHolder->SetupAttachment(RootComponent);

	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = nullptr;

	tankMoveSpeed = 2.0f;
	tankRotationSpeed = 1.25f;

	bIsDead = false;
	bIsStunned = false;
	maxHealthPoints = 2;
	currentHealthPoints = maxHealthPoints;

	currentLocation = GetActorLocation();

	stunTimer = 0.0f;
}

void ATT_TankBase::FloatingActive_Implementation()
{
}

void ATT_TankBase::PickedupPowerup_Implementation()
{
}

void ATT_TankBase::BeginPlay()
{
	Super::BeginPlay();

	tankOverlap->OnComponentBeginOverlap.AddDynamic(this, &ATT_TankBase::OnOverlapBegin);

	if(turret)
		turretSlot->SetChildActorClass(turret);
	if (powerupHolderClass)
		powerupHolder->SetChildActorClass(powerupHolderClass);


	myTurret = Cast<ATT_TankTurret>(turretSlot->GetChildActor());
	if (myTurret)
	{
		UE_LOG(LogTemp, Log, TEXT("TankBase(BeginPlay): Attached my turret."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankBase(BeginPlay): Failed to attach my turret."));
	}

	myPowerupHolder = Cast<ATT_PowerupHolder>(powerupHolder->GetChildActor());
	if (myPowerupHolder)
	{
		myPowerupHolder->SetOwningTank(this);
		UE_LOG(LogTemp, Log, TEXT("TankBase(BeginPlay): Attached my powerup holder."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankBase(BeginPlay): Failed to attach my powerup holder."));
	}

	gameMode = Cast<ATT_TinyTanksGameMode>(GetWorld()->GetAuthGameMode());
	if (gameMode)
	{
		UE_LOG(LogTemp, Log, TEXT("TankBase(BeginPlay): Found the gamemode."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankBase(BeginPlay): Failed to find the gamemode."));
	}

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

void ATT_TankBase::KillTank(bool addWin)
{
	if (!bIsDead)
	{
		bIsDead = true;

		GetNetOwningPlayer()->GetPlayerController(GetWorld())->PlayDynamicForceFeedback(1.0f, 0.5f, true, true, true, true, EDynamicForceFeedbackAction::Start);
		
		if(tankBaseMesh)
			tankBaseMesh->SetVisibility(false);

		if (myTurret)
		{
			myTurret->GetTankGunBase()->SetVisibility(false, true);
			myTurret->GetNetOwningPlayer()->GetPlayerController(GetWorld())->PlayDynamicForceFeedback(1.0f, 0.5f, true, true, true, true, EDynamicForceFeedbackAction::Start);
		}
		else
			UE_LOG(LogTemp, Error, TEXT("TankBase(KillTank): Can't find myTurret."));

		currentHealthPoints = 0;

		if(gameMode)
			gameMode->RemoveTank(this, addWin);

		TankHasDied();
	}
}

void ATT_TankBase::StunTank()
{
	if (!bIsStunned)
		bIsStunned = true;

	if(GetWorld())
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
				case EPowerupType::PT_floating:
				{
					if (currentDeffensivePowerup == EPowerupType::PT_none)
					{
						powerup->Destroy();
						currentDeffensivePowerup = EPowerupType::PT_floating;
						PickedupPowerup();
					}

					break;
				}
				case EPowerupType::PT_shild:
				{
					if (currentDeffensivePowerup == EPowerupType::PT_none)
					{
						powerup->Destroy();
						currentDeffensivePowerup = EPowerupType::PT_shild;
						PickedupPowerup();
					}

					break;
				}
				case EPowerupType::PT_missileBullet:
				{
					if (currentOffensivePowerup == EPowerupType::PT_none)
					{
						powerup->Destroy();
						currentOffensivePowerup = EPowerupType::PT_missileBullet;
						PickedupPowerup();
					}

					break;
				}
				case EPowerupType::PT_stunBullet:
				{
					if (currentOffensivePowerup == EPowerupType::PT_none)
					{
						powerup->Destroy();
						currentOffensivePowerup = EPowerupType::PT_stunBullet;
						PickedupPowerup();
					}

					break;
				}

				case EPowerupType::PT_none:
				{
					break;
				}
				default:
				{
					break;
				}
			}

			if(myPowerupHolder)
				myPowerupHolder->UpdatePowerupHolder();
		}
	}
}

void ATT_TankBase::DamageTank()
{
	if (!bIsDead && gameMode && gameMode->GetGameStarted())
	{
		if (currentHealthPoints > 0)
		{
			TankHasBeenDamaged();
			GetNetOwningPlayer()->GetPlayerController(GetWorld())->PlayDynamicForceFeedback(0.5f, 0.3f, false, true, false, true, EDynamicForceFeedbackAction::Start);

			if (myTurret)
				myTurret->GetNetOwningPlayer()->GetPlayerController(GetWorld())->PlayDynamicForceFeedback(0.5f, 0.3f, false, true, false, true, EDynamicForceFeedbackAction::Start);
			else
				UE_LOG(LogTemp, Error, TEXT("TankBase(DamageTank): Can't find myTurret."));

			currentHealthPoints--;
		}

		if (currentHealthPoints <= 0)
		{
			bIsDead = true;

			GetNetOwningPlayer()->GetPlayerController(GetWorld())->PlayDynamicForceFeedback(1.0f, 0.5f, true, true, true, true, EDynamicForceFeedbackAction::Start);

			if (myTurret)
			{
				myTurret->GetNetOwningPlayer()->GetPlayerController(GetWorld())->PlayDynamicForceFeedback(1.0f, 0.5f, true, true, true, true, EDynamicForceFeedbackAction::Start);
				myTurret->GetTankGunBase()->SetVisibility(false, true);
			}
			else
				UE_LOG(LogTemp, Error, TEXT("TankBase(DamageTank): Can't find myTurret."));

			if(tankBaseMesh)
				tankBaseMesh->SetVisibility(false);

			if(gameMode)
				gameMode->RemoveTank(this, true);
			
			TankHasDied();

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
	bIsShilded = val;
	ShieldActive();
}

void ATT_TankBase::ActivateFloating(bool val)
{
	bIsFloating = val;
	FloatingActive();
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

void ATT_TankBase::ShieldActive_Implementation()
{
}

void ATT_TankBase::UpdateTankTeam_Implementation()
{
}
