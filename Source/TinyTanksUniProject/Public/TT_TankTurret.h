// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TT_TankBaseController.h"
#include "TT_TankTurret.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class USphereComponent;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_TankTurret : public APawn
{
	GENERATED_BODY()

	///////////////////
	//// VARIABLES ////
	///////////////////

public:

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float fireRate;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float rotateSpeed;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float isOverlapped;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadwrite)
		FVector turretForwardVector;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadwrite)
		FRotator turretCurrentRotation;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadwrite)
		ESelectedTeam turretTeam;

	UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
		UStaticMeshComponent* tankGunBase;
	UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
		USphereComponent* overlapSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
		USceneComponent* fireLocation;


protected:


	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:

	ATT_TankTurret();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		FVector GetForwardVector();
	UFUNCTION()
		UStaticMeshComponent* GetTankGunBase() { return tankGunBase; };


	UFUNCTION(Category = "Tank", BlueprintCallable)
		ESelectedTeam GetTurretTeam() { return turretTeam; };

	UFUNCTION(Category = "Tank", BlueprintCallable)
		void SetTurretTeam(ESelectedTeam team);


	UFUNCTION(Category = "Tank", BlueprintNativeEvent)
		void UpdateTankTeam();

	virtual void UpdateTankTeam_Implementation();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
