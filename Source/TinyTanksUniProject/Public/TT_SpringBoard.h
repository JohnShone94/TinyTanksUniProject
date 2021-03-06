// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TT_TankBase.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "TT_SpringBoard.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UMaterial;
class ATT_TankBase;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_SpringBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATT_SpringBoard();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* SpringMesh;

	UPROPERTY(EditAnywhere)
		USphereComponent* SpringOverlap;

	UPROPERTY(Category = "Set New Location", EditAnywhere, BlueprintReadWrite)
		FVector newActorLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		ATT_TankBase* tank;

	UPROPERTY()
		FVector currentLocation;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
