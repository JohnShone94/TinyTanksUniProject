// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TT_TankBase.h"
#include "GameFramework/Actor.h"
#include "TT_Powerup.generated.h"

class UStaticMeshComponent;
class UMaterial;
class USphereComponent;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_Powerup : public AActor
{
	GENERATED_BODY()
	
	///////////////////
	//// VARIABLES ////
	///////////////////

public:	

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* powerupMesh;

	UPROPERTY(VisibleAnywhere)
		USphereComponent* powerupOverlap;

	UPROPERTY(EditAnywhere)
		float rotateSpeed;

	UPROPERTY(EditAnywhere)
		float pitchValue;

	UPROPERTY(EditAnywhere)
		float yawValue;

	UPROPERTY(EditAnywhere)
		float rollValue;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		EPowerupType powerupType;

protected:

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:	

	// Sets default values for this actor's properties
	ATT_Powerup();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		EPowerupType GetPowerupType() { return powerupType; };
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UFUNCTION()
	//	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
