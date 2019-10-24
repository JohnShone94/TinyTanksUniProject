// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankTurretController.h"
#include "TT_TankTurret.h"
#include "EngineUtils.h"
#include "TimerManager.h"

const FName ATT_TankTurretController::fireBinding("FireBinding");
const FName ATT_TankTurretController::rotateBinding("RotateBinding");

ATT_TankTurretController::ATT_TankTurretController()
{
	bCanFire = true;
}

void ATT_TankTurretController::BeginPlay()
{
	controlledPawn = Cast<ATT_TankTurret>(GetPawn());

	if (!controlledPawn)
	{
		for (TActorIterator<ATT_TankTurret> actorItr(GetWorld()); actorItr; ++actorItr)
		{
			// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
			ATT_TankTurret *actor = *actorItr;

			if (actor->GetController())
				continue;
			else
				Possess(actor);
		}

		if (!controlledPawn)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed To Possess Turret."));
		}
	}
}

void ATT_TankTurretController::PlayerTick(float DeltaTime)
{
	if (controlledPawn)
	{
		// Find movement direction
		const float rotateValue = GetInputAxisValue(rotateBinding);
		//UE_LOG(LogTemp, Warning, TEXT("ROTATE %f"), RotateValue);

		if (rotateValue != 0.0f)
		{
			//UE_LOG(LogTemp, Warning, TEXT("GUNS READY TO ROTATE"));
			const FRotator rotateDirection = (FRotator(0.0f, 1.0f, 0.0f) * rotateValue);
			controlledPawn->AddActorWorldRotation(rotateDirection);
		}

		if (GetInputAxisValue(fireBinding) != 0.0f)
		{
			const FVector fireDirection = controlledPawn->turretForwardVector;
			FireShot(fireDirection);
			//UE_LOG(LogTemp, Warning, TEXT("FIRE!!! FIRE!!! FIRE!!!"));
		}
	}
}

void ATT_TankTurretController::SetupInputComponent()
{
	InputComponent->BindAxis(rotateBinding);
	InputComponent->BindAxis(fireBinding);
}

void ATT_TankTurretController::FireShot(FVector fireDirection)
{
	// If it's ok to fire again
	if (controlledPawn && bCanFire == true && (fireDirection.SizeSquared() > 0.0f))
	{
		const FRotator fireRotation = fireDirection.Rotation();
		// Spawn projectile at an offset from this pawn
		const FVector spawnLocation = controlledPawn->GetActorLocation() + fireRotation.RotateVector(controlledPawn->gunOffset);

		UWorld* const world = GetWorld();
		if (world != NULL)
		{
			// spawn the projectile
			UE_LOG(LogTemp, Warning, TEXT("FIRE!!!"));
			//world->SpawnActor<ASpaceship>(spawnLocation, fireRotation);
		}

		bCanFire = false;
		world->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ATT_TankTurretController::ShotTimerExpired, controlledPawn->fireRate);
	}
}

void ATT_TankTurretController::ShotTimerExpired()
{
	bCanFire = true;
}