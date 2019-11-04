// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_PulseMine.h"

// Sets default values
ATT_PulseMine::ATT_PulseMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATT_PulseMine::PulseMine(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerController != nullptr)
	{

	}
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{

	}	
}

bool ATT_PulseMine::GetGenerateOverlapEvents() const
{
	return true;
}
