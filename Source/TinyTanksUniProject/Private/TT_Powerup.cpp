// Fill out your copyright notice in the Description page of Project Settings.

#include "TT_Powerup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "TT_BasicBullet.h"
#include "TT_TankBase.h"
#include "Engine.h"

// Sets default values
ATT_Powerup::ATT_Powerup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	powerupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Powerup Mesh"));
	powerupMesh->SetCollisionProfileName("OverlapAll");
	powerupMesh->SetSimulatePhysics(false);
	powerupMesh->SetEnableGravity(false);
	RootComponent = powerupMesh;

	powerupOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Powerup Overlap Component"));
	powerupOverlap->SetCollisionProfileName("OverlapAll");
	powerupOverlap->SetSimulatePhysics(false);
	powerupOverlap->SetEnableGravity(false);
	powerupOverlap->SetupAttachment(RootComponent);


	pitchValue = 0.0f;
	yawValue = 0.0f;
	rollValue = 0.0f;

}

// Called when the game starts or when spawned
void ATT_Powerup::BeginPlay()
{
	Super::BeginPlay();	
	powerupOverlap->OnComponentBeginOverlap.AddDynamic(this, &ATT_Powerup::OnOverlapBegin);
}

void ATT_Powerup::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ATT_TankBase* tank = Cast<ATT_TankBase>(OtherActor);
		if (tank)
		{
			tank->SetCurrentPowerup(powerupType);
			Destroy();
		}
	}
}

// Called every frame
void ATT_Powerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rot = FRotator(pitchValue, yawValue, rollValue);

	FQuat quat = FQuat(rot);

	AddActorLocalRotation(quat, false, 0, ETeleportType::None);
}