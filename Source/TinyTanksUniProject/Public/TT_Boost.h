// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_Boost.generated.h"

class UStaticMeshComponent;
class UMaterial;
class UBoxComponent;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_Boost : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATT_Boost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		UBoxComponent* MyBoost;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BoostPU;

	UPROPERTY(EditAnywhere)
		UParticleSystem* PickUp;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
