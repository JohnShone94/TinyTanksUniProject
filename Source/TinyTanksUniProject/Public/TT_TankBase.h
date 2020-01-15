// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TT_TankBase.generated.h"

class UStaticMeshComponent;
class ATT_BasicBullet;
class ATT_TinyTanksGameMode;
class ATT_Powerup;
class USphereComponent;

UENUM()
enum class EPowerupType
{
	PT_none					UMETA(DiaplayName = "None"),
	PT_speedBoost			UMETA(DisplayName = "Speed Boost"),

	PT_fastBullet			UMETA(DisplayName = "Fast Bullet"),
	PT_missile				UMETA(DisplayName = "Misslie"),
	PT_wallBullet			UMETA(DisplayName = "Wall Bullet"),
	PT_undergroundBullet	UMETA(DisplayName = "Undeground Bullet"),
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

	//The speed of a tank when turning.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float rotateSpeed;

	//The speed of a tank when moving forward.
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float moveSpeed;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		EPowerupType currentPowerup;

	UPROPERTY(EditAnywhere)
		USphereComponent* tankOverlap;

protected:

	UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* tankBaseMesh;

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

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadWrite)
		ATT_TinyTanksGameMode* gameMode;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		float stunTimer;

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

	UFUNCTION()
		UChildActorComponent* GetTurretSlot() { return turretSlot; };

	UFUNCTION()
		FVector GetTankForwardVector() { return tankBaseMesh->GetForwardVector(); };

	//Called when the tank dies.
	UFUNCTION(BlueprintCallable)
		void KillTank();

	//Called when the tank is stunned.
	UFUNCTION()
		void StunTank();

	//Called when the tank is damaged.
	UFUNCTION()
		void DamageTank();

	UFUNCTION(BlueprintCallable)
		void SetCanRockDestroy(bool val = true) { bCanRockDestroy = val; };

	UFUNCTION()
		void SetCurrentPowerup(EPowerupType powerup) { currentPowerup = powerup; };

	UFUNCTION()
		EPowerupType GetCurrentPowerup() { return currentPowerup; };
	
	//Called when another class needs to detect if the tank is dead.
	UFUNCTION(BlueprintCallable)
		bool GetIsDead() { return bIsDead; };

	UFUNCTION(BlueprintCallable)
		bool GetCanRockDestroy() { return bCanRockDestroy; };

	//Called when another class needs to detect if the tank is stunned.
	UFUNCTION(BlueprintCallable)
		bool GetIsStunned() { return bIsStunned; };

	//Called when another class needs to get the max health points.
	UFUNCTION(BlueprintCallable)
		int32 GetMaxHealthPoints() { return maxHealthPoints; };

	//Called when another class needs to get the current health points
	UFUNCTION(BlueprintCallable)
		int32 GetCurrentHealthPoints() { return currentHealthPoints; };

	UFUNCTION(BlueprintNativeEvent)
		void TankHasDied();

		virtual void TankHasDied_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void TankHasBeenDamaged();

		virtual void TankHasBeenDamaged_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void TankHasFired();

		virtual void TankHasFired_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void StunTimerExpired();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
