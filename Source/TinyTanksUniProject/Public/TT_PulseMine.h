// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Pawn.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "TT_PulseMine.generated.h"


UCLASS()
class TINYTANKSUNIPROJECT_API ATT_PulseMine : public AActor
{
	GENERATED_BODY()

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:	
	ATT_PulseMine();

protected:
	virtual void BeginPlay();

private:
	bool GetGenerateOverlapEvents() const;
};
