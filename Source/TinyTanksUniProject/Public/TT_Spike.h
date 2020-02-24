// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TT_Spike.generated.h"

class USceneComponent;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_Spike : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATT_Spike();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* sceneLink;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
