// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_TankBase.h"
#include "TT_MagicMissile.generated.h"

class USphereComponent;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_MagicMissile : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float baseVelocity;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float speedModifier;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float missileLifeTime;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float missileSpeed;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		int32 maxHitAmount;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		FVector velocity;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		FVector currentPosition;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		FVector targetPosition;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		FVector traceStartPoint;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		FVector traceEndPoint;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		float moveMissileDeltaTime;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		float lifeLineDeltaTime;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		bool isMoving;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		bool hasHitSomething;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		bool foundPath;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		FHitResult hit;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		int32 hitAmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USphereComponent* missileRootComp;


	UPROPERTY()
		ATT_TankBase* owningPlayer;
	UPROPERTY()
		EPowerupType currentBulletType;

	FVector hitNormal;

public:	
	// Sets default values for this actor's properties
	ATT_MagicMissile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SetupBullet(FVector fireVel, ATT_TankBase* player, EPowerupType bulletType);

	void MoveMissile(float DeltaTime);
	void CheckHitActor(AActor* hitActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector HitNormal, const FHitResult& HitResult);

};
