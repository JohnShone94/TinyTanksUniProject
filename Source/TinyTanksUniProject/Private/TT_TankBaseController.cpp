// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankBaseController.h"
#include "TT_TankBase.h"
#include "TT_TankTurret.h"
#include "TT_TinyTanksGameMode.h"
#include "GameFramework/Pawn.h"
#include "EngineUtils.h"
#include "TimerManager.h"

const FName ATT_TankBaseController::moveBinding("MoveBinding");
const FName ATT_TankBaseController::rotateBinding("RotateBinding");
const FName ATT_TankBaseController::fireBinding("FireBinding");

ATT_TankBaseController::ATT_TankBaseController()
{
	bCanFire = true;
}

void ATT_TankBaseController::BeginPlay()
{
	gameMode = Cast<ATT_TinyTanksGameMode>(GetWorld()->GetAuthGameMode());

	if (gameMode->GetPlayerPositionFromCon(this) == 0)
	{
		for (int i = 1; i < 5; i++)
		{
			if (!gameMode->GetPlayerConAtPosition(i))
			{
				gameMode->AddPlayerConAtPosition(i, this);
				break;
			}
		}
	}
	
	tankPawn = Cast<ATT_TankBase>(GetPawn());
	
	if(!tankPawn)
		turretPawn = Cast<ATT_TankTurret>(GetPawn());
}

void ATT_TankBaseController::PlayerTick(float DeltaTime)
{
	if ((gameMode->GetPlayerPositionFromCon(this) == 1 || gameMode->GetPlayerPositionFromCon(this) == 3))
	{
		// Find movement direction
		const float forwardValue = GetInputAxisValue(moveBinding);
		UE_LOG(LogTemp, Warning, TEXT("Forward %f"), forwardValue);
		const float rotateValue = GetInputAxisValue(rotateBinding);
		UE_LOG(LogTemp, Warning, TEXT("Turn %f"), rotateValue);

		if (rotateValue != 0.0f)
		{
			const FRotator rotateDirection = (FRotator(0.0f, tankPawn->rotateSpeed, 0.0f) * rotateValue);
			tankPawn->AddActorWorldRotation(rotateDirection);
			//UE_LOG(LogTemp, Warning, TEXT("ROTATE"));
		}
		else if (forwardValue != 0.0f)
		{
			FHitResult Hit(1.f);
			if (forwardValue > 0.0f)
			{
				const FVector moveDirection = ((tankPawn->tankForwardVector * tankPawn->moveSpeed) * forwardValue);
				tankPawn->AddActorWorldOffset(moveDirection, true, &Hit);
				//UE_LOG(LogTemp, Warning, TEXT("GO FORWARD"));
			}
			else if (forwardValue < 0.0f)
			{
				const FVector moveDirection = ((tankPawn->tankForwardVector * (tankPawn->moveSpeed / 4)) * forwardValue);
				tankPawn->AddActorWorldOffset(moveDirection, true, &Hit);
				//UE_LOG(LogTemp, Warning, TEXT("GO BACK"));
			}
		}
	}

	if ((gameMode->GetPlayerPositionFromCon(this) == 2 || gameMode->GetPlayerPositionFromCon(this) == 4))
	{
		// Find movement direction
		const float rotateValue = GetInputAxisValue(rotateBinding);
		UE_LOG(LogTemp, Warning, TEXT("ROTATE %f"), rotateValue);

		if (rotateValue != 0.0f)
		{
			//UE_LOG(LogTemp, Warning, TEXT("GUNS READY TO ROTATE"));
			const FRotator rotateDirection = (FRotator(0.0f, turretPawn->rotateSpeed, 0.0f) * rotateValue);
			turretPawn->AddActorWorldRotation(rotateDirection);
		}

		if (GetInputAxisValue(fireBinding) != 0.0f)
		{
			const FVector fireDirection = turretPawn->turretForwardVector;
			FireShot(fireDirection);
			//UE_LOG(LogTemp, Warning, TEXT("FIRE!!! FIRE!!! FIRE!!!"));
		}
	}
}

void ATT_TankBaseController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAxis(moveBinding);
		InputComponent->BindAxis(rotateBinding);
		InputComponent->BindAxis(fireBinding);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BASE UNABLE TO SETUP INPUT COMPONENT"));
	}
}


void ATT_TankBaseController::FireShot(FVector fireDirection)
{
	// If it's ok to fire again
	if (turretPawn && bCanFire == true && (fireDirection.SizeSquared() > 0.0f))
	{
		const FRotator fireRotation = fireDirection.Rotation();
		// Spawn projectile at an offset from this pawn
		const FVector spawnLocation = turretPawn->GetActorLocation() + fireRotation.RotateVector(turretPawn->gunOffset);

		UWorld* const world = GetWorld();
		if (world != NULL)
		{
			// spawn the projectile
			UE_LOG(LogTemp, Warning, TEXT("FIRE!!!"));
			//world->SpawnActor<ASpaceship>(spawnLocation, fireRotation);
		}

		bCanFire = false;
		world->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ATT_TankBaseController::ShotTimerExpired, turretPawn->fireRate);
	}
}

void ATT_TankBaseController::ShotTimerExpired()
{
	bCanFire = true;
}