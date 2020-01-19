// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_FloorTile.generated.h"

class UStaticMeshComponent;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_FloorTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATT_FloorTile();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* tileMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
