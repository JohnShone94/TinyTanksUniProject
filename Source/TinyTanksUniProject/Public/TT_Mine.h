// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_Mine.generated.h"

class UStaticMeshComponent;
class UMaterial;
class USphereComponent;
class ATT_TankBase;



UCLASS()
class TINYTANKSUNIPROJECT_API ATT_Mine : public AActor
{
	GENERATED_BODY()
	
public:	
	ATT_Mine();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mineMesh;

	UPROPERTY(EditAnywhere)
		USphereComponent* mineOverlapSphere;

	UPROPERTY(EditAnywhere)
		UMaterial* flashOn;

	UPROPERTY(EditAnywhere)
		UMaterial* flashOff;

	UPROPERTY(EditAnywhere)
		UParticleSystem* explosion;

protected:
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		ATT_TankBase* tank;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		bool bFlashOn;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		bool bCanFlash;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		bool bIsActivated;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		int32 countdown;

	FTimerHandle bombCountdown;

protected:

	virtual void BeginPlay();

	 UFUNCTION()
		void ChangeBomb();

	 UFUNCTION()
		 void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	 UFUNCTION()
		 void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	 UFUNCTION()
		 void OnMineOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};