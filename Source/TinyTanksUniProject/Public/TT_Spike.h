// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TT_TankBase.h"
#include "GameFramework/Actor.h"
#include "TT_Spike.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UMaterial;
class ATT_TankBase;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_Spike : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATT_Spike();

	UPROPERTY(category = "Mesh", EditAnywhere)
		UStaticMeshComponent* spikeMesh;
	UPROPERTY(category = "Collision", EditAnywhere)
		USphereComponent* spikeSphere;

	UPROPERTY(category = "Spike Meshes", EditAnywhere)
		UMaterial* spikeUp;

	UPROPERTY(category = "Spike Mehses", EditAnywhere)
		UMaterial* spikeDown;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		ATT_TankBase* tank;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bSpikeActive;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
