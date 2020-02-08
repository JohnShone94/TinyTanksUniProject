// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_Spike.h"
#include "Components/SceneComponent.h"
#include "Engine.h"

// Sets default values
ATT_Spike::ATT_Spike()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sceneLink = CreateDefaultSubobject<USceneComponent>(TEXT("Wall Scene Link"));
	RootComponent = sceneLink;


}

// Called when the game starts or when spawned
void ATT_Spike::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATT_Spike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

