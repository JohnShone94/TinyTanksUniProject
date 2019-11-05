// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_PulseMine.h"

// Sets default values
ATT_PulseMine::ATT_PulseMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool ATT_PulseMine::GetGenerateOverlapEvents() const
{
	return true;
}

void ATT_PulseMine::BeginPlay()
{
	TArray<FHitResult> ActorHits;
	FVector MyLocation = GetActorLocation();

	FVector Start = MyLocation;
	FVector End = MyLocation;
	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(500.0f);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), MyColSphere.GetSphereRadius(), 50, FColor::Cyan, true);
	bool isHit = GetWorld() ->SweepMultiByChannel(ActorHits, Start, End, FQuat::Identity, ECC_WorldStatic, MyColSphere);

	if (isHit)
	{
		for (auto& Hit : ActorHits)
		{
			UStaticMeshComponent*MeshComp = Cast<UStaticMeshComponent>((Hit.GetActor())->GetRootComponent());

			if (MeshComp)
			{
				MeshComp->AddRadialImpulse(GetActorLocation(), 500.0f, 2000000.0f, ERadialImpulseFalloff::RIF_Constant, true);
			}
		}
	}
}