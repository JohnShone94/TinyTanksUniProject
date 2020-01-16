// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TT_TankBase.h"
#include "GameFramework/Actor.h"
#include "TT_PressurePlate.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UMaterial;
class UBoxComponent;
class ATT_TankBase;

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_PressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATT_PressurePlate();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* plateMesh;

	UPROPERTY(EditAnywhere)
		USphereComponent* plateOverlap;

	UPROPERTY(EditAnywhere)
		UMaterial* PlateUp;

	UPROPERTY(EditAnywhere)
		UMaterial* PlateDown;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		ATT_TankBase* tank;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bPlateActivate;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
