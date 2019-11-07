// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TT_TankBase.generated.h"

class UStaticMeshComponent;
class ATT_BasicBullet;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_TankBase : public APawn
{
	GENERATED_BODY()

	///////////////////
	//// VARIABLES ////
	///////////////////

public:
	//The forward vector of the tank.
	UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FVector tankForwardVector;

	//The speed of a tank when turning.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float rotateSpeed;

	//The speed of a tank when moving forward.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float moveSpeed;

protected:

	UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* tankBaseMesh;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadWrite)
		UChildActorComponent* turretSlot;

	//The amount of hits a tank can take before it blows up.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		int32 maxHealthPoints;

	//The amount of hits a tank has left before it blows up.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		int32 currentHealthPoints;

	//Set to true when the tank is dead.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		bool bIsDead;

	//Set to true when the tank is stunned.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		bool bIsStunned;


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

	UFUNCTION()
		FVector GetTankForwardVector() { return tankBaseMesh->GetForwardVector(); };

	//Called when the tank dies.
	UFUNCTION()
		void KillTank();

	//Called when the tank is stunned.
	UFUNCTION()
		void StunTank();

	//Called when the tank is damaged.
	UFUNCTION()
		void DamageTank();

	//Called when another class needs to detect if the tank is dead.
	UFUNCTION()
		bool GetIsDead() { return bIsDead; };

	//Called when another class needs to detect if the tank is stunned.
	UFUNCTION()
		bool GetIsStunned() { return bIsStunned; };

	//Called when another class needs to get the max health points.
	UFUNCTION()
		int32 GetMaxHealthPoints() { return maxHealthPoints; };

	//Called when another class needs to get the current health points
	UFUNCTION()
		int32 GetCurrentHealthPoints() { return currentHealthPoints; };

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TankHasDied();

		virtual void TankHasDied_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void TankHasBeenDamaged();

		virtual void TankHasBeenDamaged_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TankHasFired();

		virtual void TankHasFired_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
