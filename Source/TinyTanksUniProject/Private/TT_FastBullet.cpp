// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_FastBullet.h"
#include "TT_TankBaseController.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine.h"

// Sets default values
ATT_FastBullet::ATT_FastBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	fastBulletStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FastBullet"));
	RootComponent = fastBulletStaticMesh;

	fastBulletCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("FastBulletComp"));
	fastBulletCollision->InitBoxExtent(FVector(60, 60, 60));
	fastBulletCollision->SetCollisionProfileName("Hit");
	fastBulletCollision->SetupAttachment(RootComponent);

	fastBulletStaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ATT_FastBullet::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ATT_FastBullet::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ATT_FastBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATT_FastBullet::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), fastBulletParticleSystem, GetActorLocation());
//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("Fast Bullet Pickup"));
		
		
		Destroy();

	}
}

