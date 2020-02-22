// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TT_TankBaseController.h"
#include "TT_TankBase.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class ATT_MagicMissile;
class ATT_Powerup;
class ATT_PressurePlate;
class ATT_SpringBoard;
class ATT_TinyTanksGameMode;
class ATT_Shield;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_TankBase : public APawn
{
	GENERATED_BODY()

	///////////////////
	//// VARIABLES ////
	///////////////////

public:
	//The forward vector of the tank.
	UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadOnly)
		FVector tankForwardVector;
	//The speed of a tank when turning.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float rotateSpeed;
	//The speed of a tank when moving forward.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float moveSpeed;
	//The amount of hits a tank can take before it blows up.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		int32 maxHealthPoints;
	//Set to true when the tank is dead.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		bool bCanRockDestroy;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		EPowerupType currentOffensivePowerup;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		EPowerupType currentDeffensivePowerup;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_MagicMissile> magicMissile;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* turretSlot;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		ATT_Shield* myShield;
	
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_TankTurret> turret;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* tankOverlap;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* tankBaseMesh;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//	USphereComponent* shildCollison;

protected:
	//The amount of hits a tank has left before it blows up.
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		int32 currentHealthPoints;
	//Set to true when the tank is dead.
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		bool bIsDead;
	//Set to true when the tank is stunned.
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		bool bIsStunned;
	//Set to true when the tank is shilded.
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		bool bIsShilded;
	//Set to true when the tank is floating.
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		bool bIsFloating;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		ATT_TinyTanksGameMode* gameMode;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		float stunTimer;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		FVector setLocation;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		FVector currentLocation;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		FVector destination;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadwrite)
		ATT_Powerup* powerupInt;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadwrite)
		ESelectedTeam tankTeam;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadwrite)
		ATT_TankTurret* myTurret;


	FTimerHandle TimerHandle_StunTimerExpired;

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:
	// Sets default values for this character's properties
	ATT_TankBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Category = "Tank", BlueprintCallable)
		UChildActorComponent* GetTurretSlot() { return turretSlot; };

	UFUNCTION(Category = "Tank", BlueprintCallable)
		FVector GetTankForwardVector() { return tankBaseMesh->GetForwardVector(); };

	UFUNCTION(Category = "Tank", BlueprintCallable)
		ESelectedTeam GetTankTeam() { return tankTeam; };

	UFUNCTION(Category = "Tank", BlueprintCallable)
		void SetTankTeam(ESelectedTeam team);

	//Called when the tank dies.
	UFUNCTION(Category = "Tank", BlueprintCallable)
		void KillTank(bool addWin = true);

	//Called when the tank is stunned.
	UFUNCTION(Category = "Tank", BlueprintCallable)
		void StunTank();

	//Called when the tank is damaged.
	UFUNCTION(Category = "Tank", BlueprintCallable)
		void DamageTank();

	UFUNCTION(Category = "Tank", BlueprintCallable)
		void SetCanRockDestroy(bool val = true) { bCanRockDestroy = val; };

	UFUNCTION(Category = "Tank", BlueprintCallable)
		void ResetOffensivePowerup();

	UFUNCTION(Category = "Tank", BlueprintCallable)
		void ActivateShild(bool val);

	UFUNCTION(Category = "Tank", BlueprintCallable)
		void ActivateFloating(bool val);

	UFUNCTION(Category = "Tank")
		void SetCurrentOffensivePowerup(EPowerupType powerup) { currentOffensivePowerup = powerup; };

	UFUNCTION(Category = "Tank", BlueprintCallable)
		EPowerupType GetCurrentOffensivePowerup() { return currentOffensivePowerup; };

	UFUNCTION(Category = "Tank", BlueprintCallable)
		void ResetDeffensivePowerup();

	UFUNCTION(Category = "Tank")
		void SetCurrentDeffensivePowerup(EPowerupType powerup) { currentDeffensivePowerup = powerup; };

	UFUNCTION(Category = "Tank", BlueprintCallable)
		EPowerupType GetCurrentDeffensivePowerup() { return currentDeffensivePowerup; };
	
	//Called when another class needs to detect if the tank is dead.
	UFUNCTION(Category = "Tank", BlueprintCallable)
		bool GetIsDead() { return bIsDead; };

	UFUNCTION(Category = "Tank", BlueprintCallable)
		bool GetCanRockDestroy() { return bCanRockDestroy; };

	//Called when another class needs to detect if the tank is stunned.
	UFUNCTION(Category = "Tank", BlueprintCallable)
		bool GetIsStunned() { return bIsStunned; };

	UFUNCTION(Category = "Tank", BlueprintCallable)
		bool GetIsShilded() { return bIsShilded; };

	UFUNCTION(Category = "Tank", BlueprintCallable)
		bool GetIsFloating() { return bIsFloating; };

	//Called when another class needs to get the max health points.
	UFUNCTION(Category = "Tank", BlueprintCallable)
		int32 GetMaxHealthPoints() { return maxHealthPoints; };

	//Called when another class needs to get the current health points
	UFUNCTION(Category = "Tank", BlueprintCallable)
		int32 GetCurrentHealthPoints() { return currentHealthPoints; };

	UFUNCTION(Category = "Tank", BlueprintNativeEvent)
		void TankHasDied();

		virtual void TankHasDied_Implementation();

	UFUNCTION(Category = "Tank", BlueprintNativeEvent)
		void TankHasBeenDamaged();

		virtual void TankHasBeenDamaged_Implementation();

	UFUNCTION(Category = "Tank", BlueprintNativeEvent)
		void TankHasFired();

		virtual void TankHasFired_Implementation();

	UFUNCTION(Category = "Tank", BlueprintNativeEvent)
		void UpdateTankTeam();

		virtual void UpdateTankTeam_Implementation();

	UFUNCTION(Category = "Tank", BlueprintNativeEvent)
		void ShieldActive();

		virtual void ShieldActive_Implementation();

	UFUNCTION(Category = "Tank", BlueprintNativeEvent)
		void FloatingActive();

		virtual void FloatingActive_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void StunTimerExpired();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
