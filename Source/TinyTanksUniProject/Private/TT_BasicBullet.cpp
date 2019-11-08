// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_BasicBullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "TT_TankBase.h"
#include "TT_TankTurret.h"
#include "TT_DestructableWall.h"
#include "TT_FallingRock.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine.h"

// Sets default values
ATT_BasicBullet::ATT_BasicBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("Bullet Mesh");

	UStaticMesh* meshToUse = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("StaticMesh'/Game/Assets/Bullet/Bullet_Low.Bullet_Low'")));
	UMaterial* materialToUse = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("Material'/Game/Blueprints/Red.Red'")));

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
	projectileMovement->InitialSpeed = 800.f;
	projectileMovement->MaxSpeed = 9000.f;
	projectileMovement->bRotationFollowsVelocity = true;
	projectileMovement->bShouldBounce = true;
	projectileMovement->Velocity = FVector(0.0f, 0.0f, 0.0f);
	projectileMovement->Bounciness = 0.5f;
	projectileMovement->Friction = -1.0f;
	projectileMovement->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 5.0f;

	maxHitAmount = 3;
}

void ATT_BasicBullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		if (OtherActor->GetClass() == this->GetClass())
		{
			Destroy();
		}
		else
		{
			ATT_TankBase* tank = Cast<ATT_TankBase>(OtherActor);
			if (tank)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Bullet hit: %s"), *tank->GetName());
				tank->DamageTank();
				Destroy();
			}
			else
			{
				ATT_DestructableWall* dWall = Cast<ATT_DestructableWall>(OtherActor);
				if (dWall)
				{
					Destroy();
				}
				else
				{
					ATT_FallingRock* fallingRock = Cast<ATT_FallingRock>(OtherActor);
					if (fallingRock)
					{
						fallingRock->Destroy();
						Destroy();
					}
					else
					{
						hitAmount++;
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Bullet bounced"));

						if (hitAmount >= maxHitAmount)
							Destroy();
					}
				}
			}
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

}

void ATT_BasicBullet::SetVelocity(FRotator fireRotation)
{
	projectileMovement->Velocity = (fireRotation.Vector() * projectileMovement->InitialSpeed);
}


