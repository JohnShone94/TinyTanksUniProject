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
		
public:	
	// Sets default values for this actor's properties
	ATT_PulseMine();

protected:
	// Called when the game starts or when spawned
		virtual void BeginPlay();
private:
	bool GetGenerateOverlapEvents() const;
	   
};
