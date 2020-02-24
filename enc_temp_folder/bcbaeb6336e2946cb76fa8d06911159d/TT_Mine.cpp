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

	mineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mine Mesh"));
	RootComponent = mineMesh;

	mineOverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Mine Overlap Component"));
	mineOverlapSphere->SetupAttachment(RootComponent);

	mineActivationSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Mine Activation Component"));
	mineActivationSphere->OnComponentBeginOverlap.AddDynamic(this, &ATT_Mine::OnMineOverlapBegin);
	mineActivationSphere->SetupAttachment(RootComponent);

	countdown = 0;
	bFlashOn = true;	
	bCanFlash = true;
	bIsActivated = false;
}

void ATT_Mine::BeginPlay()
{
	Super::BeginPlay();
	mineMesh->SetVisibility(false);


	//mineActivationSphere->OnComponentBeginOverlap.AddDynamic(this, &ATT_Mine::OnMineOverlapBegin);

	mineOverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ATT_Mine::OnOverlapBegin);
	mineOverlapSphere->OnComponentEndOverlap.AddDynamic(this, &ATT_Mine::OnOverlapEnd);
}

void ATT_Mine::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
		tank = Cast<ATT_TankBase>(OtherActor);
}

void ATT_Mine::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ATT_TankBase* leavingTank = Cast<ATT_TankBase>(OtherActor);
		if (leavingTank)
			tank = nullptr;
	}
}

void ATT_Mine::OnMineOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if(tank)
		{
			mineMesh->SetVisibility(true);
			bCanFlash = false;
			GetWorld()->GetTimerManager().SetTimer(bombCountdown, this, &ATT_Mine::ChangeBomb, 0.2f, true, 0.5f);
		}
	}

}

void ATT_Mine::ChangeBomb()
{
	if (bFlashOn == true)
	{
		mineMesh->SetMaterial(0, flashOn);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("FlashOff"));
		bFlashOn = false;
		countdown++;
	}
	else
	{
		mineMesh->SetMaterial(0, flashOff);
		bFlashOn = true;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("FlashOn"));
		countdown++;
	}

	bCanFlash = true;

	if (countdown >= 6)
	{
		if (tank)
			tank->StunTank();

		Destroy();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion, GetActorLocation());
	}
}