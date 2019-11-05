// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_BasicBullet.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATT_BasicBullet::ATT_BasicBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("Bullet Mesh");
	RootComponent = bulletMesh;

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");



}

// Called when the game starts or when spawned
void ATT_BasicBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATT_BasicBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

