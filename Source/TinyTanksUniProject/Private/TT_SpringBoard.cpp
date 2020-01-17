// Fill out your copyright notice in the Description page of Project Settings.

#include "TT_SpringBoard.h"
#include "TT_TankBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine.h"

// Sets default values
ATT_SpringBoard::ATT_SpringBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("spring Mesh"));
	SpringMesh->SetCollisionProfileName("OverlapAll");
	SpringMesh->SetSimulatePhysics(false);
	SpringMesh->SetEnableGravity(false);
	RootComponent = SpringMesh;

	SpringOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("spring overlap"));
	SpringOverlap->SetSimulatePhysics(false);
	SpringOverlap->SetEnableGravity(false);
	SpringOverlap->SetupAttachment(RootComponent);

	currentLocation = GetActorLocation;

}

// Called when the game starts or when spawned
void ATT_SpringBoard::BeginPlay()
{
	Super::BeginPlay();

	SpringOverlap->OnComponentBeginOverlap.AddDynamic(this, &ATT_SpringBoard::OnOverlapBegin);
	SpringOverlap->OnComponentEndOverlap.AddDynamic(this, &ATT_SpringBoard::OnOverlapEnd);	
}

// Called every frame
void ATT_SpringBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugLine(GetWorld(),currentLocation, newActorLocation, FColor(255,0,0))

}
void ATT_SpringBoard::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		tank = Cast<ATT_TankBase>(OtherActor);
	}
}

void ATT_SpringBoard::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ATT_TankBase* leavingTank = Cast<ATT_TankBase>(OtherActor);
		if (leavingTank)
			tank = nullptr;
	}
}