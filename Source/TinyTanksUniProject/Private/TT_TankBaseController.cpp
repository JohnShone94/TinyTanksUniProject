// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankBaseController.h"
#include "TT_TankTurret.h"
#include "TT_MagicMissile.h"
#include "TT_TinyTanksGameMode.h"

#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Pawn.h"
#include "EngineUtils.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"

ATT_TankBaseController::ATT_TankBaseController()
{
	bCanFire = true;
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
		InputComponent->BindAxis("RotateBind", this, &ATT_TankBaseController::Rotate);
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
			tankPawn->ActivateFloating(false);
			tankPawn->ResetDeffensivePowerup();
		}
		else if (activeDeffensivePowerup == EPowerupType::PT_shild)
		{
			tankPawn->ActivateShild(false);
			tankPawn->ResetDeffensivePowerup();
		}
		activeDeffensivePowerup = EPowerupType::PT_none;
	}
}

void ATT_TankBaseController::MoveForward(float val)
{
	if (tankPawn && gameMode && gameMode->GetCanPlayersControlTanks() && !tankPawn->GetIsDead() && !tankPawn->GetIsStunned() && val != 0.0f && (gameMode->GetPlayerPositionFromCon(this) == 1 || gameMode->GetPlayerPositionFromCon(this) == 3) )
	{

		float speedMultiplier;
		speedMultiplier = 1.0f;

		//UE_LOG(LogTemp, Warning, TEXT("TANK FORWARD %f"), val);
		FHitResult Hit(1.0f);
		if (val > 0.0f)
		{

			const FVector moveDirection = ((tankPawn->GetTankForwardVector() * tankPawn->moveSpeed * speedMultiplier) * val);
			tankPawn->AddActorWorldOffset(FVector(moveDirection.X, moveDirection.Y, 0.0f), false, &Hit);
		}
		else if (val < 0.0f)
		{
			const FVector moveDirection = ((tankPawn->GetTankForwardVector()* ((tankPawn->moveSpeed * speedMultiplier) / 2.5)) * val);
			tankPawn->AddActorWorldOffset(FVector(moveDirection.X, moveDirection.Y, 0.0f), false, &Hit);
		}
	}
}
void ATT_TankBaseController::Rotate(float val)
{

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

					ATT_MagicMissile* bullet = world->SpawnActor<ATT_MagicMissile>(turretParent->magicMissile, spawnTransform, SpawnParams);
					if(bullet)
						bullet->SetupBullet(fireDirection, turretParent, activeOffensivePowerup);
					
					if (activeOffensivePowerup != EPowerupType::PT_none)
					{
						turretParent->ResetOffensivePowerup();
						activeOffensivePowerup = EPowerupType::PT_none;
					}
				}

				bCanFire = false;

				world->GetTimerManager().SetTimer(fireMissileTimerHandle, this, &ATT_TankBaseController::ShotTimerExpired, turretPawn->fireRate);
			}
		}
	}
}

void ATT_TankBaseController::ActivateSpecial(float val)
{
	if (gameMode && gameMode->GetCanPlayersControlTanks() && val > 0.0f )
	{
		if (tankPawn && (tankPawn->currentDeffensivePowerup == EPowerupType::PT_shild || tankPawn->currentDeffensivePowerup == EPowerupType::PT_floating) && !tankPawn->GetIsFloating() && !tankPawn->GetIsShilded())
		{
			activeDeffensivePowerup = tankPawn->currentDeffensivePowerup;
		}
		else if (turretPawn)
		{
			ATT_TankBase* turretParent = Cast<ATT_TankBase>(turretPawn->GetParentActor());
			if (turretParent && (turretParent->currentOffensivePowerup == EPowerupType::PT_stunBullet || turretParent->currentOffensivePowerup == EPowerupType::PT_missileBullet))
			{
				activeOffensivePowerup = turretParent->currentOffensivePowerup;
			}
		}
	}
}

void ATT_TankBaseController::UseSpecial(float val)
{
	if (tankPawn && gameMode && gameMode->GetCanPlayersControlTanks() && val > 0.0f && !tankPawn->GetIsFloating() && !tankPawn->GetIsShilded())
	{
		if (activeDeffensivePowerup == EPowerupType::PT_floating)
		{
			tankPawn->ActivateFloating(true);
			GetWorld()->GetTimerManager().SetTimer(powerupTimerHandle, this, &ATT_TankBaseController::SpecialTimerExpired, 5.0f);
		}
		else if (activeDeffensivePowerup == EPowerupType::PT_shild)
		{
			tankPawn->ActivateShild(true);
			GetWorld()->GetTimerManager().SetTimer(powerupTimerHandle, this, &ATT_TankBaseController::SpecialTimerExpired, 5.0f);
		}
	}
}
