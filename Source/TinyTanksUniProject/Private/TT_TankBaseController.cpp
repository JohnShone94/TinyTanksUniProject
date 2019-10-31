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
	Super::BeginPlay();
	gameMode = Cast<ATT_TinyTanksGameMode>(GetWorld()->GetAuthGameMode());

	if (gameMode && gameMode->GetPlayerPositionFromCon(this) == 0)
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
}
//
//void ATT_TankBaseController::PlayerTick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//	if ((gameMode->GetPlayerPositionFromCon(this) == 1 || gameMode->GetPlayerPositionFromCon(this) == 3))
//	{
//		// Find movement direction
//		const float forwardValue = GetInputAxisValue(moveBinding);
//		UE_LOG(LogTemp, Warning, TEXT("Forward %f"), forwardValue);
//		const float rotateValue = GetInputAxisValue(rotateBinding);
//		UE_LOG(LogTemp, Warning, TEXT("Turn %f"), rotateValue);
//
//		if (rotateValue != 0.0f)
//		{
//			const FRotator rotateDirection = (FRotator(0.0f, tankPawn->rotateSpeed, 0.0f) * rotateValue);
//			tankPawn->AddActorWorldRotation(rotateDirection);
//			//UE_LOG(LogTemp, Warning, TEXT("ROTATE"));
//		}
//		else if (forwardValue != 0.0f)
//		{
//			FHitResult Hit(1.f);
//			if (forwardValue > 0.0f)
//			{
//				const FVector moveDirection = ((tankPawn->tankForwardVector * tankPawn->moveSpeed) * forwardValue);
//				tankPawn->AddActorWorldOffset(moveDirection, true, &Hit);
//				//UE_LOG(LogTemp, Warning, TEXT("GO FORWARD"));
//			}
//			else if (forwardValue < 0.0f)
//			{
//				const FVector moveDirection = ((tankPawn->tankForwardVector * (tankPawn->moveSpeed / 4)) * forwardValue);
//				tankPawn->AddActorWorldOffset(moveDirection, true, &Hit);
//				//UE_LOG(LogTemp, Warning, TEXT("GO BACK"));
//			}
//		}
//	}
//}

void ATT_TankBaseController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAxis("MoveBinding", this, &ATT_TankBaseController::MoveForward);
		InputComponent->BindAxis("RotateBinding", this, &ATT_TankBaseController::Rotate);
		InputComponent->BindAxis("FireBinding", this, &ATT_TankBaseController::FireShot);

		UE_LOG(LogTemp, Warning, TEXT("SETUP INPUT COMPONENT"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BASE UNABLE TO SETUP INPUT COMPONENT"));
	}
}


void ATT_TankBaseController::ShotTimerExpired()
{
	bCanFire = true;
}

void ATT_TankBaseController::MoveForward(float val)
{
	if (tankPawn && val != 0.0f && (gameMode->GetPlayerPositionFromCon(this) == 1 || gameMode->GetPlayerPositionFromCon(this) == 3))
	{
		UE_LOG(LogTemp, Warning, TEXT("Forward %f"), val);
		FHitResult Hit(1.0f);
		if (val > 0.0f)
		{
			const FVector moveDirection = ((tankPawn->GetTankForwardVector() * tankPawn->moveSpeed) * val);
			tankPawn->AddActorWorldOffset(moveDirection, true, &Hit);
		}
		else if (val < 0.0f)
		{
			const FVector moveDirection = ((tankPawn->GetTankForwardVector()* (tankPawn->moveSpeed / 4)) * val);
			tankPawn->AddActorWorldOffset(moveDirection, true, &Hit);
		}
	}
}
void ATT_TankBaseController::Rotate(float val)
{
	if (tankPawn && val != 0.0f && (gameMode->GetPlayerPositionFromCon(this) == 1 || gameMode->GetPlayerPositionFromCon(this) == 3))
	{
		UE_LOG(LogTemp, Warning, TEXT("Turn %f"), val);
		const FRotator rotateDirection = (FRotator(0.0f, tankPawn->rotateSpeed, 0.0f) * val);
		tankPawn->AddActorWorldRotation(rotateDirection);
	}

	if (turretPawn && val != 0.0f && (gameMode->GetPlayerPositionFromCon(this) == 2 || gameMode->GetPlayerPositionFromCon(this) == 4))
	{
		UE_LOG(LogTemp, Warning, TEXT("ROTATE %f"), val);
		const FRotator rotateDirection = (FRotator(0.0f, turretPawn->rotateSpeed, 0.0f) * val);
		turretPawn->AddActorWorldRotation(rotateDirection);
	}
}

void ATT_TankBaseController::FireShot(float val)
{
	if (turretPawn && val != 0.0f &&(gameMode->GetPlayerPositionFromCon(this) == 2 || gameMode->GetPlayerPositionFromCon(this) == 4))
	{
		const FVector fireDirection = turretPawn->turretForwardVector;

		if (turretPawn && bCanFire == true && (fireDirection.SizeSquared() > 0.0f))
		{
			const FRotator fireRotation = fireDirection.Rotation();

			const FVector spawnLocation = turretPawn->GetActorLocation() + fireRotation.RotateVector(turretPawn->gunOffset);

			UWorld* const world = GetWorld();
			if (world != NULL)
			{
				//UE_LOG(LogTemp, Warning, TEXT("FIRE!!!"));
				//world->SpawnActor<ASpaceship>(spawnLocation, fireRotation);
			}

			bCanFire = false;

			world->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ATT_TankBaseController::ShotTimerExpired, turretPawn->fireRate);
		}
	}
}