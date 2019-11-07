// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_Mine.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine.h"

// Sets default values
ATT_Mine::ATT_Mine()
{
	PrimaryActorTick.bCanEverTick = true;

	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombMesh"));
	RootComponent = BombMesh;

	MyBombMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("BombComponent"));
	MyBombMesh->InitBoxExtent(FVector(50, 50, 50));
	MyBombMesh->SetCollisionProfileName("Hit");
	MyBombMesh->SetupAttachment(RootComponent);

	//FlashOn = CreateAbstractDefaultSubobject<UMaterial>(TEXT("FlashOnMat"));
	//FlashOff = CreateAbstractDefaultSubobject<UMaterial>(TEXT("FlashOffMat"));

	BombMesh->OnComponentBeginOverlap.AddDynamic(this, &ATT_Mine::OnOverlapBegin);
	//BombMesh->bGenerateCollisionEvents = true;

//	int TimesFlashed = 4;
	bFlashOn = true;	
	bCanFlash = true;
}

void ATT_Mine::BeginPlay()
{
	Super::BeginPlay();

	//BombMesh->SetMaterial(0, FlashOff);
}

void ATT_Mine::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	float Countdown = 0.5f;	

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (bCanFlash)
		{
			bCanFlash = false;

			GetWorld()->GetTimerManager().SetTimer(BombCountdown, this, &ATT_Mine::ChangeBomb, 1.0f, true, 1.0f);

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("Hello There!"));
		}
	}
}

void ATT_Mine::ChangeBomb()
{
//	int TimesFlashed = 420;
	if (bFlashOn == true)
	{
		BombMesh->SetMaterial(0, FlashOn);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("FlashOff"));

		bFlashOn = false;
	}
	else
	{
		BombMesh->SetMaterial(0, FlashOff);

		bFlashOn = true;

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("FlashOn"));

//		int TimesFlashed;

//		if (TimesFlashed>=4)
//		{
//
//			Destroy();
//		}
	}
	bCanFlash = true;

}