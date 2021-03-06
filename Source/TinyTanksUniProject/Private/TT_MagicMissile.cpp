// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_MagicMissile.h"
#include "TT_DestructableWall.h"
#include "TT_StandardWall.h"
#include "TT_Shield.h"
#include "EngineUtils.h"
#include "TimerManager.h"
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
	bIsDestroyed = false;
	bIsBlueTeam = false;
	finishedsetup = false;
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

	if (!bIsDestroyed)
		MoveMissile(DeltaTime);

	lifeLineDeltaTime += 0.1f;

	if (lifeLineDeltaTime >= missileLifeTime && !bIsDestroyed)
		RunBulletHitEffect();
}

void ATT_MagicMissile::SetupFinished_Implementation()
{

}

void ATT_MagicMissile::DeathTimerExpired()
{
	this->Destroy();
}

void ATT_MagicMissile::SetupBullet(FVector fireVel, ATT_TankBase* player, EPowerupType bulletType)
{
	owningPlayer = player;
	currentBulletType = bulletType;

	if (player->GetTankTeam() == ESelectedTeam::ST_teamOneBase)
		bIsBlueTeam = true;
	else
		bIsBlueTeam = false;

	switch (currentBulletType)
	{
		case EPowerupType::PT_none:
		{
			velocity = ((fireVel * baseVelocity) * speedModifier);

			break;
		}
		case EPowerupType::PT_missileBullet:
		{
			velocity = ((fireVel * baseVelocity) * (speedModifier * 2));
			maxHitAmount += 2;
			RunMegaBulletEffect();

			break;
		}
		case EPowerupType::PT_stunBullet:
		{
			velocity = ((fireVel * baseVelocity) * speedModifier);

			break;
		}
		default:
			break;
	}

	finishedsetup = true;

	SetupFinished();
}

void ATT_MagicMissile::MoveMissile(float DeltaTime)
{
	UWorld* world = this->GetWorld();
	if (world && !bIsDestroyed)
	{
		traceStartPoint = this->GetActorLocation();
		traceEndPoint = traceStartPoint + (velocity * moveMissileDeltaTime);
		traceEndPoint.Z = traceStartPoint.Z;
		moveMissileDeltaTime += 10.0f;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("DeltaTime: %f"), testDeltaTime));

		FCollisionQueryParams collisionParams;
		collisionParams.AddIgnoredActor(this);

		hasHitSomething = GetWorld()->LineTraceSingleByChannel(hit, traceStartPoint, traceEndPoint, ECC_GameTraceChannel7, collisionParams);

		//DrawDebugLine(world, traceStartPoint, traceEndPoint, FColor::Red, true);

		if (hasHitSomething && hit.GetActor())
		{
			currentPosition = traceStartPoint;
			targetPosition = hit.Location;

			//DrawDebugLine(world, traceStartPoint, traceEndPoint, FColor::Blue, true, 1.0f);

			if (GetActorLocation().Equals(targetPosition, 1.0f) && isMoving)
			{
				if (hitAmount < maxHitAmount)
				{
					hitAmount++;

					FVector riqochetVelocity;
					//FVector hitNormal = hit.Normal;
					if (FMath::IsNearlyEqual(hitNormal.X, 1.0f, 0.1f) || FMath::IsNearlyEqual(hitNormal.X, -1.0f, 0.1f))
					{
						riqochetVelocity = FVector((velocity.X * -1.0f), velocity.Y, 0.0f);
					}
					else if (FMath::IsNearlyEqual(hitNormal.Y, 1.0f, 0.1f) || FMath::IsNearlyEqual(hitNormal.Y, -1.0f, 0.1f))
					{
						riqochetVelocity = FVector(velocity.X, (velocity.Y * -1.0f), 0.0f);
					}
					else
					{
						riqochetVelocity = FVector((velocity.X * -1.0f), (velocity.Y * -1.0f), 0.0f);
					}

					velocity = riqochetVelocity;
					traceEndPoint = currentPosition;
					SetActorRotation(riqochetVelocity.Rotation());
					moveMissileDeltaTime = 0.01f;
					missileRootComp->MoveIgnoreActors.Empty();
					isMoving = false;
				}
				else
				{
					RunBulletHitEffect();
				}
			}
			else
			{
				//FVector newLoc = FMath::Lerp(currentPosition, targetPosition, missileSpeed);
				FVector newLoc = currentPosition + (velocity * (missileSpeed * DeltaTime));

				FHitResult out;
				SetActorLocation(newLoc, true, &out);

				if (out.GetActor())
				{
					hitNormal = out.Normal;

					ATT_StandardWall* wall = Cast<ATT_StandardWall>(out.GetActor());
					if (wall) 
					{
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Hit Wall with Vector: %s"), *hitNormal.ToString()), true, FVector2D(2.0f, 2.0f));
						missileRootComp->IgnoreActorWhenMoving(wall, true);
					}
					else if (out.GetActor()->ActorHasTag("Arena_ArenaWall"))
					{
					//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Hit arena wall with Vector: %s"), *hitNormal.ToString()), true, FVector2D(2.0f, 2.0f));
						missileRootComp->IgnoreActorWhenMoving(out.GetActor(), true);
					}
					else if (out.GetActor() == owningPlayer && hitAmount < 1)
					{
						missileRootComp->IgnoreActorWhenMoving(out.GetActor(), true);
					}
					else
					{
						ATT_Shield* shield = Cast<ATT_Shield>(out.GetActor());
						if (shield && owningPlayer && owningPlayer->GetShield() && shield == owningPlayer->GetShield())
						{
							missileRootComp->IgnoreActorWhenMoving(out.GetActor(), true);
						}
					}
				}

				isMoving = true;
				currentPosition = newLoc;
			}
		}
	}

}

void ATT_MagicMissile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector HitNormal, const FHitResult & HitResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hit Class: %s"), *OtherActor->GetName()));

	if (OtherActor->GetClass() == this->GetClass())
	{
		RunBulletHitEffect();
	}
	else if (!bIsDestroyed)
	{
		ATT_TankBase* tank = Cast<ATT_TankBase>(OtherActor);
		if (tank && owningPlayer)
		{
			if (tank == owningPlayer && hitAmount <= 0)
			{

			}
			else
			{
				missileRootComp->MoveIgnoreActors.Empty();
				if (currentBulletType == EPowerupType::PT_missileBullet)
				{
					tank->DamageTank();
					tank->DamageTank();
				}
				else if (currentBulletType == EPowerupType::PT_stunBullet)
					tank->StunTank();
				else
					tank->DamageTank();

				RunBulletHitEffect();
			}
		}
		else
		{
			ATT_DestructableWall* dWall = Cast<ATT_DestructableWall>(OtherActor);
			if (dWall)
				RunBulletHitEffect();
			else
			{
				ATT_Shield* shield = Cast<ATT_Shield>(OtherActor);
				if (shield && tank && tank->GetShield() && shield == tank->GetShield())
				{

				}
				else if (shield)
				{
					missileRootComp->MoveIgnoreActors.Empty();
					RunBulletHitEffect();
				}

			}
		}
	}
}

void ATT_MagicMissile::RunBulletHitEffect_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Can be destroyed")));
	bIsDestroyed = true;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_DeathTimerExpired, this, &ATT_MagicMissile::DeathTimerExpired, 0.5f);
}

void ATT_MagicMissile::RunMegaBulletEffect_Implementation()
{
}