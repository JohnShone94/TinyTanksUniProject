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
	
}

void ATT_Mine::BeginPlay()
{
	Super::BeginPlay();

	//DrawDebugBox(GetWorld(), GetActorLocation(), FVector(100, 100, 100), FColor::Purple, true, -1, 0, 10);

	//BombMesh->SetMaterial(0, FlashOff);
}

void ATT_Mine::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	float Countdown = 0.5f;	

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
			GetWorld()->GetTimerManager().SetTimer(BombCountdown, this, &ATT_Mine::ChangeBomb, 0.5f, true, 0.1f);

			BombMesh->SetMaterial(0, FlashOff);

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("Hello There!"));		
	}
}

void ATT_Mine::ChangeBomb()
{
	int BombTimer = 4;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("FlashOn"));
	BombMesh->SetMaterial(0, FlashOn);

	if (--BombTimer >0)
	{
		//GetWorldTimerManager().ClearTimer(BombCountdown);

		BombMesh->SetMaterial(0, FlashOff);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("FlashOff"));
	}

	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Else"));
		GetWorldTimerManager().ClearTimer(BombCountdown);
	}

	//GetWorld()->GetTimerManager().SetTimer(BombCountdown, this, &ATT_Mine::ChangeBomb, 0.5f, true, 0.1f);

}