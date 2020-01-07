// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "TT_MainCamera.generated.h"

/**
 * 
 */
UCLASS()
class TINYTANKSUNIPROJECT_API ATT_MainCamera : public ACameraActor
{
	GENERATED_BODY()

	///////////////////
	//// VARIABLES ////
	///////////////////

public:
	UFUNCTION(BlueprintNativeEvent)
		void LastManIsStanding();

	///////////////////
	//// FUNCTIONS ////
	///////////////////

	ATT_MainCamera();
	virtual void LastManIsStanding_Implementation();
	
};
