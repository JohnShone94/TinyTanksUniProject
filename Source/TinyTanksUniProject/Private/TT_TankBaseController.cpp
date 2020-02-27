// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankBaseController.h"
#include "TT_TankTurret.h"
#include "TT_MagicMissile.h"
#include "TT_TinyTanksGameMode.h"
#include "TT_PowerupHolder.h"

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
	speedMultiplier = 0.0f;
	rotateMultiplier = 0.0f;
	i = 0.0f;
}

void ATT_TankBaseController::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<ATT_TinyTanksGameMode>(GetWorld()->GetAuthGameMode());

	GrabSecondaryActors();
}

void ATT_TankBaseController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (speedMultiplier != 0.0f)
	{
		if (tankPawn && gameMode && gameMode->GetCanPlayersControlTanks() && !tankPawn->GetIsDead() && !tankPawn->GetIsStunned() && (gameMode->GetPlayerPositionFromCon(this) == 1 || gameMode->GetPlayerPositionFromCon(this) == 3))
		{
			FHitResult Hit(1.0f);
			if (speedMultiplier > 0.0f)
			{
				FVector oldLocation = tankPawn->GetActorLocation();
				const FVector moveDirection = (tankPawn->GetTankForwardVector() * ((tankPawn->tankMoveSpeed * DeltaTime) * speedMultiplier));
				tankPawn->AddActorWorldOffset(FVector(moveDirection.X, moveDirection.Y, 0.0f), false, &Hit);
			
				//if (Hit.GetActor() && Hit.GetActor()->ActorHasTag("PlayerIgnore"))
				//{
				//	tankPawn->MoveIgnoreActorAdd(Hit.GetActor());
				//}

				//UE_LOG(LogTemp, Warning, TEXT("TankBaseController(MoveTank): Tank Speed: %f, Speed Multiplier: %f, DeltaTime: %f, Overall Speed: %f"), tankPawn->tankMoveSpeed, speedMultiplier, DeltaTime, ((tankPawn->tankMoveSpeed * DeltaTime) * speedMultiplier));
			}
			else if (speedMultiplier < 0.0f)
			{
				const FVector moveDirection = ((tankPawn->GetTankForwardVector() * ((tankPawn->tankMoveSpeed * DeltaTime) / 2.5)) * speedMultiplier);
				tankPawn->AddActorWorldOffset(FVector(moveDirection.X, moveDirection.Y, 0.0f), false, &Hit);

				//UE_LOG(LogTemp, Warning, TEXT("TankBaseController(MoveTank): Tank Speed: %f, Speed Multiplier: %f, Controller Val: %f, Overall Speed: %f"), tankPawn->tankMoveSpeed, speedMultiplier, val, ((tankPawn->tankMoveSpeed * speedMultiplier) * val));
			}
		}
	}

	if (rotateMultiplier != 0.0f)
	{
		if (tankPawn && gameMode && gameMode->GetCanPlayersControlTanks() && !tankPawn->GetIsDead() && !tankPawn->GetIsStunned() && (gameMode->GetPlayerPositionFromCon(this) == 1 || gameMode->GetPlayerPositionFromCon(this) == 3))
		{
			//UE_LOG(LogTemp, Warning, TEXT("TANK TURN %f"), val);
			const FRotator rotateDirection = ((FRotator(0.0f, tankPawn->tankRotationSpeed, 0.0f) * DeltaTime) * rotateMultiplier);
			tankPawn->AddActorWorldRotation(rotateDirection);

			if (tankPawn->GetAttchedPowerupHolder())
				tankPawn->GetAttchedPowerupHolder()->SetActorRotation(tankPawn->GetAttchedPowerupHolder()->holderCurrentRotation);

			if (tankTurretChild)
				tankTurretChild->SetActorRotation(tankTurretChild->turretCurrentRotation);
			else if (GrabSecondaryActors() && tankTurretChild)
				tankTurretChild->SetActorRotation(tankTurretChild->turretCurrentRotation);

		}

		if (turretPawn && gameMode && gameMode->GetCanPlayersControlTanks())
		{
			if (!turretTankParent)
				GrabSecondaryActors();

			if (turretTankParent && !turretTankParent->GetIsDead() && !turretTankParent->GetIsStunned() && (gameMode->GetPlayerPositionFromCon(this) == 2 || gameMode->GetPlayerPositionFromCon(this) == 4))
			{
				//UE_LOG(LogTemp, Warning, TEXT("TURRET ROTATE %f"), val);
				const FRotator rotateDirection = ((FRotator(0.0f, turretPawn->rotateSpeed, 0.0f) * DeltaTime) * rotateMultiplier);
				turretPawn->AddActorWorldRotation(rotateDirection);
				turretPawn->turretCurrentRotation = turretPawn->GetActorRotation();
			}
		}
	}

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
		}
		else if (activeDeffensivePowerup == EPowerupType::PT_shild)
		{
			tankPawn->ActivateShild(false);
		}
		activeDeffensivePowerup = EPowerupType::PT_none;
	}
}

void ATT_TankBaseController::MoveForward(float val)
{
	speedMultiplier = val;
}
void ATT_TankBaseController::Rotate(float val)
{
	rotateMultiplier = val;
}

void ATT_TankBaseController::FireShot(float val)
{
	if (turretPawn && gameMode && gameMode->GetCanPlayersControlTanks())
	{
		if (!turretTankParent)
			GrabSecondaryActors();

		if (turretTankParent && !turretTankParent->GetIsDead() && !turretTankParent->GetIsStunned() && val != 0.0f && (gameMode->GetPlayerPositionFromCon(this) == 2 || gameMode->GetPlayerPositionFromCon(this) == 4))
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
					SpawnParams.Owner = turretTankParent;
					SpawnParams.Instigator = Instigator;

					FTransform spawnTransform = FTransform(fireRotation, spawnLocation, FVector(1.0f, 1.0f, 1.0f));

					ATT_MagicMissile* bullet = world->SpawnActor<ATT_MagicMissile>(turretTankParent->magicMissile, spawnTransform, SpawnParams);
					if(bullet)
						bullet->SetupBullet(fireDirection, turretTankParent, activeOffensivePowerup);
					
					if ((turretTankParent->GetCurrentOffensivePowerup() == EPowerupType::PT_stunBullet || turretTankParent->GetCurrentOffensivePowerup() == EPowerupType::PT_missileBullet))
					{
						activeOffensivePowerup = turretTankParent->GetCurrentOffensivePowerup();
					}

					if (activeOffensivePowerup != EPowerupType::PT_none)
					{
						turretTankParent->ResetOffensivePowerup();
						activeOffensivePowerup = EPowerupType::PT_none;

						if (turretTankParent->GetAttchedPowerupHolder())
							turretTankParent->GetAttchedPowerupHolder()->UpdatePowerupHolder();

					}

					turretTankParent->TankHasFired();
				}

				bCanFire = false;

				world->GetTimerManager().SetTimer(fireMissileTimerHandle, this, &ATT_TankBaseController::ShotTimerExpired, turretPawn->fireRate);
			}
		}
	}
}

void ATT_TankBaseController::ActivateSpecial(float val)
{
	//if (gameMode && gameMode->GetCanPlayersControlTanks() && val > 0.0f )
	//{
	//	if (tankPawn && (tankPawn->GetCurrentDeffensivePowerup() == EPowerupType::PT_shild || tankPawn->GetCurrentDeffensivePowerup() == EPowerupType::PT_floating) && !tankPawn->GetIsFloating() && !tankPawn->GetIsShilded())
	//	{
	//		activeDeffensivePowerup = tankPawn->GetCurrentDeffensivePowerup();
	//	}
	//	else if (turretPawn)
	//	{
	//		if (!turretTankParent)
	//			GrabSecondaryActors();

	//		if (turretTankParent && (turretTankParent->GetCurrentOffensivePowerup() == EPowerupType::PT_stunBullet || turretTankParent->GetCurrentOffensivePowerup() == EPowerupType::PT_missileBullet))
	//		{
	//			activeOffensivePowerup = turretTankParent->GetCurrentOffensivePowerup();
	//		}
	//	}
	//}
}

void ATT_TankBaseController::UseSpecial(float val)
{
	if (tankPawn && gameMode && gameMode->GetCanPlayersControlTanks() && val > 0.0f && !tankPawn->GetIsFloating() && !tankPawn->GetIsShilded())
	{

		if ((tankPawn->GetCurrentDeffensivePowerup() == EPowerupType::PT_shild || tankPawn->GetCurrentDeffensivePowerup() == EPowerupType::PT_floating) && !tankPawn->GetIsFloating() && !tankPawn->GetIsShilded())
		{
			activeDeffensivePowerup = tankPawn->GetCurrentDeffensivePowerup();
		}

		if (activeDeffensivePowerup == EPowerupType::PT_floating)
		{
			tankPawn->ActivateFloating(true);
			tankPawn->ResetDeffensivePowerup();
			GetWorld()->GetTimerManager().SetTimer(powerupTimerHandle, this, &ATT_TankBaseController::SpecialTimerExpired, 5.0f);
		}
		else if (activeDeffensivePowerup == EPowerupType::PT_shild)
		{
			tankPawn->ActivateShild(true);
			tankPawn->ResetDeffensivePowerup();
			GetWorld()->GetTimerManager().SetTimer(powerupTimerHandle, this, &ATT_TankBaseController::SpecialTimerExpired, 5.0f);
		}

		if (tankPawn->GetAttchedPowerupHolder())
			tankPawn->GetAttchedPowerupHolder()->UpdatePowerupHolder();
	}
}

bool ATT_TankBaseController::GrabSecondaryActors()
{
	if (tankPawn)
	{
		tankTurretChild = Cast<ATT_TankTurret>(tankPawn->GetAttachedTurret());
		if (tankTurretChild)
		{
			UE_LOG(LogTemp, Warning, TEXT("TankBaseController(BeginPlay): Successfully grabbed the child turret of tank: %s"), *tankPawn->GetName());
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("TankBaseController(BeginPlay): Failed to grab the child turret of tank: %s"), *tankPawn->GetName());
			return false;
		}
	}

	if (turretPawn)
	{
		turretTankParent = Cast<ATT_TankBase>(turretPawn->GetParentActor());
		if (turretTankParent)
		{
			UE_LOG(LogTemp, Warning, TEXT("TankBaseController(BeginPlay): Successfully grabbed the adult tank of turret: %s"), *turretPawn->GetName());
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("TankBaseController(BeginPlay): Failed to grab the adult tank of turret: %s"), *turretPawn->GetName());
			return false;
		}
	}

	return false; //Only returns false here if both of the above statements fail. 
}
