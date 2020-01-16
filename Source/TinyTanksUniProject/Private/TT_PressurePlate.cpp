// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_PressurePlate.h"
#include "TT_TankBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine.h"

// Sets default values
ATT_PressurePlate::ATT_PressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	plateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mine Mesh"));
	plateMesh->SetCollisionProfileName("OverlapAll");
	plateMesh->SetSimulatePhysics(false);
	plateMesh->SetEnableGravity(false);
	RootComponent = plateMesh;

	plateOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Pressure Plate Overlap Component"));
	plateOverlap->SetCollisionProfileName("OverlapAll");
	plateOverlap->SetSimulatePhysics(false);
	plateOverlap->SetEnableGravity(false);
	plateOverlap->SetupAttachment(RootComponent);

	bPlateActivate = false;
}

// Called when the game starts or when spawned
void ATT_PressurePlate::BeginPlay()
{
	Super::BeginPlay();

	plateOverlap->OnComponentBeginOverlap.AddDynamic(this, &ATT_PressurePlate::OnOverlapBegin);
	plateOverlap->OnComponentEndOverlap.AddDynamic(this, &ATT_PressurePlate::OnOverlapEnd);
	
}

// Called every frame
void ATT_PressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATT_PressurePlate::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		tank = Cast<ATT_TankBase>(OtherActor);
		plateMesh->SetMaterial(0, PlateDown);
		bPlateActivate = true;
	}
}

void ATT_PressurePlate::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ATT_TankBase* leavingTank = Cast<ATT_TankBase>(OtherActor);
		if (leavingTank)
			tank = nullptr;

		plateMesh->SetMaterial(0, PlateUp);
		bPlateActivate = false;
	}
}

