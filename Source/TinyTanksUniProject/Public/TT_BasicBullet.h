// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_BasicBullet.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_BasicBullet : public AActor
{
	GENERATED_BODY()
	

	///////////////////
	//// VARIABLES ////
	///////////////////

//public:
	//UPROPERTY(Category = "Default", VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))

protected:

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* bulletMesh;
	//UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//	USphereComponent* collision;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int32 hitAmount;
	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 maxHitAmount;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* projectileMovement;


	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:
	// Sets default values for this character's properties
	ATT_BasicBullet();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SetVelocity(FRotator fireRotation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
