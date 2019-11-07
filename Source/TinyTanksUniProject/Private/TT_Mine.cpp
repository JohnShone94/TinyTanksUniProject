// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_Mine.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "TT_TankBase.h"
#include "Engine.h"

// Sets default values
ATT_Mine::ATT_Mine()
{
	PrimaryActorTick.bCanEverTick = true;

	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombMesh"));
	RootComponent = BombMesh;

	MyBombMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("BombComponent"));
	MyBombMesh->InitBoxExtent(FVector(60, 60, 60));
	MyBombMesh->SetCollisionProfileName("Hit");
	MyBombMesh->SetupAttachment(RootComponent);

	BombMesh->OnComponentBeginOverlap.AddDynamic(this, &ATT_Mine::OnOverlapBegin);

	Countdown = 0;
	bFlashOn = true;	
	bCanFlash = true;
}

void ATT_Mine::BeginPlay()
{
	Super::BeginPlay();
}

void ATT_Mine::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		tank = Cast<ATT_TankBase>(OtherActor);

		if (tank && bCanFlash)
		{
			bCanFlash = false;

			GetWorld()->GetTimerManager().SetTimer(BombCountdown, this, &ATT_Mine::ChangeBomb, 0.5f, true, 1.0f);

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("Hello There!"));
		}

	}
}

void ATT_Mine::ChangeBomb()
{
	if (bFlashOn == true)
	{
		BombMesh->SetMaterial(0, FlashOn);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("FlashOff"));

		bFlashOn = false;

		Countdown++;
	}
	else
	{
		BombMesh->SetMaterial(0, FlashOff);

		bFlashOn = true;

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("FlashOn"));

		Countdown++;

	}
	bCanFlash = true;

	if (Countdown >= 4)
	{
		if (tank)
			tank->StunTank();
			Destroy();
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation());
	}
}