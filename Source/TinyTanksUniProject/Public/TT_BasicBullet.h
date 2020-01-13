// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_BasicBullet.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UProjectileMovementComponent;

UENUM()
enum EBulletType
{
	e_basicBullet	UMETA(DiaplayName = "Basic Bullet"),
	e_fastBullet	UMETA(DisplayName = "Fast Bullet"),
	e_Missile	    UMETA(DisplayName = "Misslie"),
};


UCLASS()
class TINYTANKSUNIPROJECT_API ATT_BasicBullet : public AActor
{
	GENERATED_BODY()
	

	///////////////////
	//// VARIABLES ////
	///////////////////

protected:

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* bulletMesh;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* missileMesh;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int32 hitAmount;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 maxHitAmount;
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int32 speedLoss;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* projectileMovement;

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:
	ATT_BasicBullet();
	virtual void Tick(float DeltaTime) override;
	float speedMiltiplier;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EBulletType BulletType;

	UPROPERTY(EditAnywhere)
		UParticleSystem* explosion;

	UFUNCTION()
		void SetVelocity(FRotator fireRotation);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector HitNormal, const FHitResult& Hit);
};
