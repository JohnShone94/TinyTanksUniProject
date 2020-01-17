// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TT_TankBase.generated.h"

class UStaticMeshComponent;
class ATT_BasicBullet;
class ATT_TinyTanksGameMode;
class ATT_Powerup;
class ATT_PressurePlate;
class ATT_SpringBoard;
class USphereComponent;

UENUM()
enum class EPowerupType
{
	PT_none						UMETA(DiaplayName = "None"),

	PT_speedBoost				UMETA(DisplayName = "Speed Boost | Neutral"),

	PT_airblast					UMETA(DisplayName = "Airblast | Defensive"),
	PT_shild					UMETA(DisplayName = "Shild | Defensive"),
	PT_smokeScreen				UMETA(DisplayName = "Smoke Screen | Defensive"),
	PT_floating					UMETA(DisplayName = "Floating | Defensive"),

	PT_fastBullet				UMETA(DisplayName = "Fast Bullet | Offensive"),
	PT_missileBullet			UMETA(DisplayName = "Misslie Bullet | Offensive"),
	PT_stunBullet				UMETA(DisplayName = "Stun Bullet | Offensive"),
	PT_undergroundBullet		UMETA(DisplayName = "Undeground Bullet | Offensive"),
};

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

	/*UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FVector newActorLocation;*/

	//The speed of a tank when turning.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float rotateSpeed;

	//The speed of a tank when moving forward.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float moveSpeed;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		EPowerupType currentOffensivePowerup;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		EPowerupType currentDeffensivePowerup;

	UPROPERTY(EditAnywhere)
		USphereComponent* tankOverlap;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATT_BasicBullet> bullet;

	UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* tankBaseMesh;
protected:

	UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* shildMesh;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadWrite)
		UChildActorComponent* turretSlot;

	//The amount of hits a tank can take before it blows up.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		int32 maxHealthPoints;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		int32 powerupNumber;

	//The amount of hits a tank has left before it blows up.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		int32 currentHealthPoints;

	//Set to true when the tank is dead.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		bool bIsDead;

	//Set to true when the tank is dead.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		bool bCanRockDestroy;

	//Set to true when the tank is stunned.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		bool bIsStunned;

	//Set to true when the tank is shilded.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		bool bIsShilded;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadWrite)
		ATT_TinyTanksGameMode* gameMode;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float stunTimer;

	UPROPERTY()
		FVector setLocation;

	FTimerHandle TimerHandle_StunTimerExpired;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadwrite)
		ATT_Powerup* powerupInt;

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

	//Called when the tank dies.
	UFUNCTION(Category = "Tank", BlueprintCallable)
		void KillTank();

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void StunTimerExpired();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
