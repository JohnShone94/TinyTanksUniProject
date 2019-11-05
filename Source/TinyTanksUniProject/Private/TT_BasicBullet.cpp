// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_BasicBullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "TT_TankBase.h"
#include "TT_TankTurret.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine.h"

// Sets default values
ATT_BasicBullet::ATT_BasicBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UStaticMesh* meshToUse = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("StaticMesh'/Game/Assets/Bullet/Bullet_Low.Bullet_Low'")));
	UMaterial* materialToUse = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("Material'/Game/Blueprints/Red.Red'")));

	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("Bullet Mesh");
	if(meshToUse)
		bulletMesh->SetStaticMesh(meshToUse);
	if (materialToUse)
		bulletMesh->GetStaticMesh()->SetMaterial(0, materialToUse);
	bulletMesh->BodyInstance.SetCollisionProfileName("BlockAll");
	bulletMesh->OnComponentHit.AddDynamic(this, &ATT_BasicBullet::OnHit);
	bulletMesh->SetNotifyRigidBodyCollision(true);
	bulletMesh->SetSimulatePhysics(false);
	bulletMesh->SetEnableGravity(false);
	RootComponent = bulletMesh;



	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	projectileMovement->UpdatedComponent = RootComponent;
	projectileMovement->InitialSpeed = 500.f;
	projectileMovement->MaxSpeed = 6000.f;
	projectileMovement->bRotationFollowsVelocity = true;
	projectileMovement->bShouldBounce = true;
	projectileMovement->Velocity = FVector(0.0f, 0.0f, 0.0f);
	projectileMovement->Bounciness = 0.2f;
	projectileMovement->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 5.0f;

	maxHitAmount = 2;
}

void ATT_BasicBullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor || (OtherActor->GetClass() != this->GetClass()))
	{
		ATT_TankBase* tank = Cast<ATT_TankBase>(OtherActor);
		if (tank)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Bullet hit: %s"), *tank->GetName());
			Destroy();
		}
		else
		{
			hitAmount++;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Bullet bounced"));
		}
	}
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

	if (hitAmount >= maxHitAmount)
		Destroy();

}

void ATT_BasicBullet::SetVelocity(FRotator fireRotation)
{
	projectileMovement->Velocity = (fireRotation.Vector() * projectileMovement->InitialSpeed);
}


