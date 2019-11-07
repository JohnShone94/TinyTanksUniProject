// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_Mine.generated.h"

class UStaticMeshComponent;
class UMaterial;
class UBoxComponent;
class ATT_TankBase;



UCLASS()
class TINYTANKSUNIPROJECT_API ATT_Mine : public AActor
{
	GENERATED_BODY()
	
public:	
	ATT_Mine();

	FTimerHandle BombCountdown;

protected:

	virtual void BeginPlay();


	UPROPERTY()
		ATT_TankBase* tank;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		bool bFlashOn;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		bool bCanFlash;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		int32 Countdown;

public:
	
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BombMesh;

	UPROPERTY(EditAnywhere)
		UMaterial* FlashOn;

	 UPROPERTY(EditAnywhere)
		UMaterial* FlashOff;

	 UPROPERTY()
		UBoxComponent* MyBombMesh;

	 UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	 void ChangeBomb();
};