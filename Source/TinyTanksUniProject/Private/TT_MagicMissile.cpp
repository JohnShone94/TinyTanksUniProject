// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_MagicMissile.h"
#include "TT_DestructableWall.h"
#include "TT_StandardWall.h"
#include "EngineUtils.h"
#include "CollisionQueryParams.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ATT_MagicMissile::ATT_MagicMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	missileRootComp = CreateDefaultSubobject<USphereComponent>(TEXT("Missile Root Component"));
	RootComponent = missileRootComp;

	velocity = FVector(1000.0f);
	missileLifeTime = 5.0f;
	missileSpeed = 0.05;
	isMoving = false;
	maxHitAmount = 3;
	hitAmount = 0;
	speedModifier = 1.0f;
	baseVelocity = 600.0f;
	moveMissileDeltaTime = 0.0f;
	lifeLineDeltaTime = 0.0f;
}

// Called when the game starts or when spawned
void ATT_MagicMissile::BeginPlay()
{
	Super::BeginPlay();
	missileRootComp->OnComponentHit.AddDynamic(this, &ATT_MagicMissile::OnHit);
}

// Called every frame
void ATT_MagicMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveMissile(DeltaTime);

	lifeLineDeltaTime += 0.1f;

	if (lifeLineDeltaTime >= missileLifeTime)
	{
		Destroy();
	}
}

void ATT_MagicMissile::SetupBullet(FVector fireVel, ATT_TankBase* player, EPowerupType bulletType)
{
	owningPlayer = player;
	currentBulletType = bulletType;
	velocity = ((fireVel * baseVelocity) * speedModifier);
}

void ATT_MagicMissile::MoveMissile(float DeltaTime)
{

	traceStartPoint = this->GetActorLocation();
	traceEndPoint = traceStartPoint + (velocity * moveMissileDeltaTime);
	traceEndPoint.Z = traceStartPoint.Z;
	moveMissileDeltaTime += 10.0f;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("DeltaTime: %f"), testDeltaTime));

	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(this);

	UWorld* world = this->GetWorld();
	if (world)
	{
		hasHitSomething = GetWorld()->LineTraceSingleByChannel(hit, traceStartPoint, traceEndPoint, ECC_GameTraceChannel7, collisionParams);

		//DrawDebugLine(world, traceStartPoint, traceEndPoint, FColor::Red, true);

		if (hasHitSomething && hit.GetActor())
		{
			currentPosition = traceStartPoint;
			targetPosition = hit.Location;
			isMoving = true;
			//DrawDebugLine(world, traceStartPoint, traceEndPoint, FColor::Blue, true);

			if (GetActorLocation().Equals(targetPosition, 1.0f))
			{
				if (hitAmount < maxHitAmount)
				{
					hitAmount++;

					FVector riqochetVelocity;
					FVector hitNormal = hit.Normal;
					if (hitNormal.X == 1.0f || hitNormal.X == -1.0f)
					{
						riqochetVelocity = FVector((velocity.X * -1.0f), velocity.Y, velocity.Z);
					}
					else if (hitNormal.Y == 1.0f || hitNormal.Y == -1.0f)
					{
						riqochetVelocity = FVector(velocity.X, (velocity.Y * -1.0f), velocity.Z);
					}

					velocity = riqochetVelocity;
					traceEndPoint = currentPosition;
					SetActorRotation(riqochetVelocity.Rotation());
					moveMissileDeltaTime = 0.01f;
					isMoving = false;
				}
				else
				{
					Destroy();
				}
			}
			else
			{
				FVector newLoc = FMath::Lerp(currentPosition, targetPosition, missileSpeed);

				FHitResult out;
				SetActorLocation(newLoc, true, &out);

				if (out.GetActor())
				{
					ATT_StandardWall* wall = Cast<ATT_StandardWall>(out.GetActor());
					if (wall)
						missileRootComp->IgnoreActorWhenMoving(wall, true);
					else if (out.GetActor()->ActorHasTag("Arena_ArenaWall"))
						missileRootComp->IgnoreActorWhenMoving(out.GetActor(), true);
				}

				currentPosition = newLoc;
			}
		}
	}

}

void ATT_MagicMissile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector HitNormal, const FHitResult & HitResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hit Class: %s"), *OtherActor->GetName()));

	if (OtherActor->GetClass() == this->GetClass())
	{
		Destroy();
	}
	else
	{
		ATT_TankBase* tank = Cast<ATT_TankBase>(OtherActor);
		if (tank && owningPlayer)
		{
			if (tank == owningPlayer && hitAmount > 0)
			{

			}
			else
			{
				if (currentBulletType == EPowerupType::PT_fastBullet)
				{
					tank->DamageTank();
				}
				else if (currentBulletType == EPowerupType::PT_missileBullet)
				{
					tank->DamageTank();
					tank->DamageTank();
				}
				else if (currentBulletType == EPowerupType::PT_stunBullet)
				{
					tank->StunTank();
				}
				else if (currentBulletType == EPowerupType::PT_undergroundBullet)
				{
					tank->DamageTank();
				}
				else
				{
					tank->DamageTank();
				}

				Destroy();
			}
		}
		else
		{
			ATT_DestructableWall* dWall = Cast<ATT_DestructableWall>(OtherActor);
			if (dWall)
			{
				Destroy();
			}
		}
	}
}


void ATT_MagicMissile::CheckHitActor(AActor * hitActor)
{
}
