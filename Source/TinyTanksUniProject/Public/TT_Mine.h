// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_Mine.generated.h"

class UStaticMeshComponent;
class UMaterialInterface;
class UBoxComponent;


UCLASS()
class TINYTANKSUNIPROJECT_API ATT_Mine : public AActor
{
	GENERATED_BODY()
	
public:	
	ATT_Mine();

protected:

	virtual void BeginPlay();

public:
	
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BombMesh;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* FlashOn;

	 UPROPERTY(EditAnywhere)
		UMaterialInterface* FlashOff;

	 UPROPERTY()
		UBoxComponent* MyBombMesh;

	 UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	 void ChangeBomb();
};