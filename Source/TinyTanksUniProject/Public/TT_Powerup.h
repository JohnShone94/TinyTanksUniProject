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
	
public:	
	// Sets default values for this actor's properties
	ATT_Powerup();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* powerupMesh;

	UPROPERTY(EditAnywhere)
		USphereComponent* powerupOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float powerupXPos;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float powerupYPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float powerupZPos;

	UPROPERTY(Category = "Default", EditAnywhere, BlueprintReadWrite)
		EPowerupType powerupType;

	UFUNCTION(BlueprintCallable)
		EPowerupType GetPowerupType() { return powerupType; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		ATT_TankBase* tank;



	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
