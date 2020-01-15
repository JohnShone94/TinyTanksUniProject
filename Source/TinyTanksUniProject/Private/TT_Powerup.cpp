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
	powerupMesh->BodyInstance.SetCollisionProfileName("OverlapAll");
	powerupMesh->SetSimulatePhysics(false);
	powerupMesh->SetEnableGravity(false);
	RootComponent = powerupMesh;

	powerupOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Mine Overlap Component"));
	powerupOverlap->BodyInstance.SetCollisionProfileName("OverlapAll");
	powerupOverlap->SetSimulatePhysics(false);
	powerupOverlap->SetEnableGravity(false);
	powerupOverlap->SetupAttachment(RootComponent);

	powerupOverlap->OnComponentBeginOverlap.AddDynamic(this, &ATT_Powerup::OnOverlapBegin);
	powerupOverlap->OnComponentEndOverlap.AddDynamic(this, &ATT_Powerup::OnOverlapEnd);


	
}

// Called when the game starts or when spawned
void ATT_Powerup::BeginPlay()
{
	Super::BeginPlay();	

	powerupOverlap->SetVisibility(false);
}

void ATT_Powerup::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		tank = Cast<ATT_TankBase>(OtherActor);

		/*if (powerupNo == 1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Fast Pickup"));
		}
		else if (powerupNo == 2)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Missile Pickup"));
		}
		else if (powerupNo == 3)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("3"));
		}
		else if (powerupNo == 4)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("4"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("0"));
		}*/

		Destroy();
	}
}

void ATT_Powerup::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ATT_TankBase* leavingTank = Cast<ATT_TankBase>(OtherActor);
		if (leavingTank)
			tank = nullptr;
	}
}

// Called every frame
void ATT_Powerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}