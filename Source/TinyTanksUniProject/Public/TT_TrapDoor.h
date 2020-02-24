// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_TrapDoor.generated.h"


class USceneComponent;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_TrapDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATT_TrapDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* sceneLink;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
