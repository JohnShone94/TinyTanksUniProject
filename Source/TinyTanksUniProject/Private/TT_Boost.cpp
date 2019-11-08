// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_Boost.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine.h"

// Sets default values
ATT_Boost::ATT_Boost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoostPU = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoostPU"));
	RootComponent = BoostPU;

	MyBoost = CreateDefaultSubobject<UBoxComponent>(TEXT("Pickup"));
	MyBoost->InitBoxExtent(FVector(50, 50, 50));
	MyBoost->SetCollisionProfileName("Hit");
	MyBoost->SetupAttachment(RootComponent);

	BoostPU->OnComponentBeginOverlap.AddDynamic(this, &ATT_Boost::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ATT_Boost::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATT_Boost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATT_Boost::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("Boost Pickup"));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickUp, GetActorLocation());

		//Tank speed up

		Destroy();
	}
}

