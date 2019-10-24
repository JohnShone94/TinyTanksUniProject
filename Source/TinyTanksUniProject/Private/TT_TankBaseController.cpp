// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_TankBaseController.h"
#include "TT_TankBase.h"
#include "EngineUtils.h"

const FName ATT_TankBaseController::moveBinding("MoveBinding");
const FName ATT_TankBaseController::rotateBinding("RotateBinding");

ATT_TankBaseController::ATT_TankBaseController()
{

}

void ATT_TankBaseController::BeginPlay()
{
	controlledPawn = Cast<ATT_TankBase>(GetPawn());

	if (!controlledPawn)
	{
		for (TActorIterator<ATT_TankBase> actorItr(GetWorld()); actorItr; ++actorItr)
		{
			// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
			ATT_TankBase *actor = *actorItr;

			if (actor->GetController())
				continue;
			else
				Possess(actor);
		}

		if (!controlledPawn)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed To Possess Base."));
		}
	}
}

void ATT_TankBaseController::PlayerTick(float DeltaTime)
{
	if (controlledPawn)
	{
		// Find movement direction
		const float forwardValue = GetInputAxisValue(moveBinding);
		//UE_LOG(LogTemp, Warning, TEXT("Forward %f"), ForwardValue);
		const float rotateValue = GetInputAxisValue(rotateBinding);
		//UE_LOG(LogTemp, Warning, TEXT("Turn %f"), RotateValue);

		if (rotateValue != 0.0f)
		{
			const FRotator rotateDirection = (FRotator(0.0f, 1.0f, 0.0f) * rotateValue);
			controlledPawn->AddActorWorldRotation(rotateDirection);
			//UE_LOG(LogTemp, Warning, TEXT("ROTATE"));
		}
		else if (forwardValue != 0.0f)
		{
			FHitResult Hit(1.f);
			if (forwardValue > 0.0f)
			{
				const FVector moveDirection = ((controlledPawn->tankForwardVector * controlledPawn->moveSpeed) * forwardValue);
				controlledPawn->AddActorWorldOffset(moveDirection, true, &Hit);
				//UE_LOG(LogTemp, Warning, TEXT("GO FORWARD"));
			}
			else if (forwardValue < 0.0f)
			{
				const FVector moveDirection = ((controlledPawn->tankForwardVector * (controlledPawn->moveSpeed / 4)) * forwardValue);
				controlledPawn->AddActorWorldOffset(moveDirection, true, &Hit);
				//UE_LOG(LogTemp, Warning, TEXT("GO BACK"));
			}
		}
	}
}

void ATT_TankBaseController::SetupInputComponent()
{
	InputComponent->BindAxis(moveBinding);
	InputComponent->BindAxis(rotateBinding);
}
