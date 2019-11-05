// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_BasicBullet.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_BasicBullet : public AActor
{
	GENERATED_BODY()
	

	///////////////////
	//// VARIABLES ////
	///////////////////

//public:
	//UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))

protected:

	UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* bulletMesh;

	UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* projectileMovement;


	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:
	// Sets default values for this character's properties
	ATT_BasicBullet();

	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
