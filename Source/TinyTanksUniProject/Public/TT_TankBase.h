// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TT_TankBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_TankBase : public APawn
{
	GENERATED_BODY()

	///////////////////
	//// VARIABLES ////
	///////////////////

public:
	UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FVector tankForwardVector;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float rotateSpeed;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float moveSpeed;

protected:

	UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* tankBaseMesh;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadWrite)
		UChildActorComponent* turretSlot;


	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:
	// Sets default values for this character's properties
	ATT_TankBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		UChildActorComponent* GetTurretSlot() { return turretSlot; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
