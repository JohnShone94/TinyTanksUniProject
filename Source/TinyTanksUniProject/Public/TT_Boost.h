// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_Boost.generated.h"

class UStaticMeshComponent;
class UMaterial;
class UBoxComponent;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_Boost : public AActor
{
	GENERATED_BODY()

	///////////////////
	//// VARIABLES ////
	///////////////////

protected:	
	UPROPERTY()
		UBoxComponent* boostCollision;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* boostStaticMesh;
	UPROPERTY(EditAnywhere)
		UParticleSystem* boostParticleSystem;

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:
	ATT_Boost();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
