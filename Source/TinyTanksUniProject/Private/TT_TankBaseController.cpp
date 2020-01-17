// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankBaseController.h"
#include "TT_TankTurret.h"
#include "TT_BasicBullet.h"
#include "TT_TinyTanksGameMode.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "EngineUtils.h"
#include "TimerManager.h"

const FName ATT_TankBaseController::moveBinding("MoveBinding");
const FName ATT_TankBaseController::rotateBinding("RotateBinding");
const FName ATT_TankBaseController::fireBinding("FireBinding");
const FName ATT_TankBaseController::activateSpecialBinding("ActivateSpecialBinding");
const FName ATT_TankBaseController::useSpecialBinding("UseSpecialBinding");

ATT_TankBaseController::ATT_TankBaseController()
{
	bCanFire = true;
	rotatingBase = false;
	activeOffensivePowerup = EPowerupType::PT_none;
}

void ATT_TankBaseController::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<ATT_TinyTanksGameMode>(GetWorld()->GetAuthGameMode());
}

void ATT_TankBaseController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAxis("MoveBinding", this, &ATT_TankBaseController::MoveForward);
		InputComponent->BindAxis("RotateBinding", this, &ATT_TankBaseController::Rotate);
		InputComponent->BindAxis("FireBinding", this, &ATT_TankBaseController::FireShot);
		InputComponent->BindAxis("ActivateSpecialBinding", this, &ATT_TankBaseController::ActivateSpecial);
		InputComponent->BindAxis("UseSpecialBinding", this, &ATT_TankBaseController::UseSpecial);

		if(InputComponent)
			UE_LOG(LogTemp, Warning, TEXT("TankBaseController(SetupInputComponent): Successfully setup Input Component."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankBaseController(SetupInputComponent): Failed to setup Input Component."));
	}
}


void ATT_TankBaseController::ShotTimerExpired()
{
	bCanFire = true;
}

void ATT_TankBaseController::SpecialTimerExpired()
{
	if (tankPawn)
	{
		if (activeDeffensivePowerup == EPowerupType::PT_floating)
		{
			tankPawn->tankBaseMesh->SetEnableGravity(true);
		}
		else if (activeDeffensivePowerup == EPowerupType::PT_shild)
		{
			tankPawn->ActivateShild(false);
		}
		else if (activeDeffensivePowerup == EPowerupType::PT_speedBoost)
		{
			tankPawn->moveSpeed = (tankPawn->moveSpeed / 2);
		}
		activeDeffensivePowerup = EPowerupType::PT_none;
	}
}

void ATT_TankBaseController::MoveForward(float val)
{
	if (tankPawn && gameMode && gameMode->GetCanPlayersControlTanks() && !tankPawn->GetIsDead() && !tankPawn->GetIsStunned() && !rotatingBase && val != 0.0f && (gameMode->GetPlayerPositionFromCon(this) == 1 || gameMode->GetPlayerPositionFromCon(this) == 3) )
	{
		//UE_LOG(LogTemp, Warning, TEXT("TANK FORWARD %f"), val);
		FHitResult Hit(1.0f);
		if (val > 0.0f)
		{
			const FVector moveDirection = ((tankPawn->GetTankForwardVector() * tankPawn->moveSpeed) * val);
			tankPawn->AddActorWorldOffset(moveDirection, false, &Hit);
		}
		else if (val < 0.0f)
		{
			const FVector moveDirection = ((tankPawn->GetTankForwardVector()* (tankPawn->moveSpeed / 2.5)) * val);
			tankPawn->AddActorWorldOffset(moveDirection, false, &Hit);
		}
	}
}
void ATT_TankBaseController::Rotate(float val)
{
	if(val == 0.0f)
		rotatingBase = false;

	if (tankPawn && gameMode && gameMode->GetCanPlayersControlTanks() && !tankPawn->GetIsDead() && !tankPawn->GetIsStunned() && val != 0.0f && (gameMode->GetPlayerPositionFromCon(this) == 1 || gameMode->GetPlayerPositionFromCon(this) == 3))
	{
		//UE_LOG(LogTemp, Warning, TEXT("TANK TURN %f"), val);
		const FRotator rotateDirection = (FRotator(0.0f, tankPawn->rotateSpeed, 0.0f) * val);
		tankPawn->AddActorWorldRotation(rotateDirection);
	}

	if (turretPawn && gameMode && gameMode->GetCanPlayersControlTanks())
	{
		ATT_TankBase* turretParent = Cast<ATT_TankBase>(turretPawn->GetParentActor());
		if (turretParent && !turretParent->GetIsDead() && !turretParent->GetIsStunned() && val != 0.0f && (gameMode->GetPlayerPositionFromCon(this) == 2 || gameMode->GetPlayerPositionFromCon(this) == 4))
		{
			//UE_LOG(LogTemp, Warning, TEXT("TURRET ROTATE %f"), val);
			const FRotator rotateDirection = (FRotator(0.0f, turretPawn->rotateSpeed, 0.0f) * val);
			turretPawn->AddActorWorldRotation(rotateDirection);
		}
	}
}

void ATT_TankBaseController::FireShot(float val)
{
	if (turretPawn && gameMode && gameMode->GetCanPlayersControlTanks())
	{
		ATT_TankBase* turretParent = Cast<ATT_TankBase>(turretPawn->GetParentActor());
		if (turretParent && !turretParent->GetIsDead() && !turretParent->GetIsStunned() && val != 0.0f && (gameMode->GetPlayerPositionFromCon(this) == 2 || gameMode->GetPlayerPositionFromCon(this) == 4))
		{
			const FVector fireDirection = turretPawn->GetForwardVector();

			if (turretPawn && bCanFire == true && (fireDirection.SizeSquared() > 0.0f))
			{
				const FRotator fireRotation = FRotator(fireDirection.Rotation().Pitch, fireDirection.Rotation().Yaw, 0.0f);

				const FVector spawnLocation = turretPawn->fireLocation->GetComponentLocation();

				UWorld* const world = GetWorld();
				if (world != NULL)
				{
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = turretParent;
					SpawnParams.Instigator = Instigator;

					FTransform spawnTransform = FTransform(fireRotation, spawnLocation, FVector(1.0f, 1.0f, 1.0f));

					ATT_BasicBullet* bullet = world->SpawnActor<ATT_BasicBullet>(turretParent->bullet, spawnTransform, SpawnParams);

					if (bullet)
					{
						if (activeOffensivePowerup != EPowerupType::PT_none)
						{
							bullet->SetupBullet(turretParent, activeOffensivePowerup, fireRotation.Vector());
							activeOffensivePowerup = EPowerupType::PT_none;
						}
						else
							bullet->SetupBullet(turretParent, EPowerupType::PT_none, fireDirection);

						turretParent->TankHasFired();
					}
				}

				bCanFire = false;

				world->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ATT_TankBaseController::ShotTimerExpired, turretPawn->fireRate);
			}
		}
	}
}

void ATT_TankBaseController::ActivateSpecial(float val)
{
	if (gameMode && gameMode->GetCanPlayersControlTanks() && val > 0.0f)
	{
		if (tankPawn && (tankPawn->currentDeffensivePowerup == EPowerupType::PT_airblast || tankPawn->currentDeffensivePowerup == EPowerupType::PT_floating || tankPawn->currentDeffensivePowerup == EPowerupType::PT_shild || tankPawn->currentDeffensivePowerup == EPowerupType::PT_smokeScreen))
		{
			activeDeffensivePowerup = tankPawn->currentDeffensivePowerup;
			tankPawn->ResetDeffensivePowerup();
		}
		else if (turretPawn)
		{
			ATT_TankBase* turretParent = Cast<ATT_TankBase>(turretPawn->GetParentActor());
			if (turretParent && (turretParent->currentOffensivePowerup == EPowerupType::PT_stunBullet || turretParent->currentOffensivePowerup == EPowerupType::PT_undergroundBullet || turretParent->currentOffensivePowerup == EPowerupType::PT_missileBullet || turretParent->currentOffensivePowerup == EPowerupType::PT_fastBullet))
			{
				activeOffensivePowerup = turretParent->currentOffensivePowerup;
				turretParent->ResetOffensivePowerup();
			}
		}
	}
}

void ATT_TankBaseController::UseSpecial(float val)
{
	if (tankPawn && gameMode && gameMode->GetCanPlayersControlTanks() && val > 0.0f)
	{
		if (activeDeffensivePowerup == EPowerupType::PT_airblast)
		{
			
		}
		else if (activeDeffensivePowerup == EPowerupType::PT_floating)
		{
			tankPawn->tankBaseMesh->SetEnableGravity(false);
		}
		else if (activeDeffensivePowerup == EPowerupType::PT_shild)
		{
			tankPawn->ActivateShild(true);
		}
		else if (activeDeffensivePowerup == EPowerupType::PT_speedBoost)
		{
			tankPawn->moveSpeed = (tankPawn->moveSpeed * 2);
		}
	}

}
