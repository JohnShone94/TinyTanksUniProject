// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_FastBullet.generated.h"


class UStaticMeshComponent;
class UMaterial;
class UBoxComponent;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_FastBullet : public AActor
{
	GENERATED_BODY()
	
	///////////////////
	//// VARIABLES ////
	///////////////////

public:	
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* fastBulletStaticMesh;

	UPROPERTY(EditAnywhere)
		UParticleSystem* fastBulletParticleSystem;

	UPROPERTY()
		UBoxComponent* fastBulletCollision;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:
	ATT_FastBullet();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
