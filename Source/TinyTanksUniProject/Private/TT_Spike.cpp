// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_Spike.h"
#include "TT_TankBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine.h"

// Sets default values
ATT_Spike::ATT_Spike()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spikeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spike Mesh"));
	spikeMesh->SetCollisionProfileName("OverlapAll");
	spikeMesh->SetSimulatePhysics(false);
	spikeMesh->SetEnableGravity(false);
	RootComponent = spikeMesh;

	spikeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Spike Overlap"));
	spikeSphere->SetCollisionProfileName("OverlapAll");
	spikeSphere->SetSimulatePhysics(false);
	spikeSphere->SetEnableGravity(false);
	spikeSphere->SetupAttachment(RootComponent);

	bSpikeActive = false;


}

// Called when the game starts or when spawned
void ATT_Spike::BeginPlay()
{
	Super::BeginPlay();

	spikeSphere->OnComponentBeginOverlap.AddDynamic(this, &ATT_Spike::OnOverlapBegin);
	spikeSphere->OnComponentEndOverlap.AddDynamic(this, &ATT_Spike::OnOverlapEnd);
	
}

// Called every frame
void ATT_Spike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATT_Spike::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		tank = Cast<ATT_TankBase>(OtherActor);
		spikeMesh->SetMaterial(0, spikeDown);
		bSpikeActive = true;
	}
}

void ATT_Spike::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ATT_TankBase* leavingTank = Cast<ATT_TankBase>(OtherActor);
		if (leavingTank)
			tank = nullptr;

		spikeMesh->SetMaterial(0, spikeDown);
		bSpikeActive = false;
	}
}

