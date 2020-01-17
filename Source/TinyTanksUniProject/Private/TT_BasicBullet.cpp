// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_BasicBullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "TT_TankTurret.h"
#include "TT_TankBase.h"
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
	bulletMesh->SetCollisionProfileName("BlockAll");
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

	overlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap Component"));
	overlapSphere->SetCollisionProfileName("OverlapAll");
	overlapSphere->SetSimulatePhysics(false);
	overlapSphere->SetEnableGravity(false);
	overlapSphere->SetupAttachment(RootComponent);
	
	speedLoss = 1.0f;
	InitialLifeSpan = 5.0f;

	maxHitAmount = 3;
}

void ATT_BasicBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector HitNormal, const FHitResult& Hit)
{
	if (OtherActor)
	{
		ATT_TankBase* tank = Cast<ATT_TankBase>(OtherActor);
		if (tank)
		{
			if (currentBulletType == EPowerupType::PT_fastBullet)
			{
				tank->DamageTank();
			}
			else if (currentBulletType == EPowerupType::PT_missileBullet && owningPlayer && (OtherActor != owningPlayer))
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
		else if (OtherActor->GetClass() == this->GetClass())
		{
			Destroy();
		}
		else
		{
			if (currentBulletType == EPowerupType::PT_fastBullet || currentBulletType == EPowerupType::PT_missileBullet || currentBulletType == EPowerupType::PT_stunBullet || currentBulletType == EPowerupType::PT_undergroundBullet)
			{
				Destroy();
			}
			else
			{
				FVector bounceBackVel = (-1 * FVector::DotProduct(projectileMovement->Velocity, HitNormal) * HitNormal + projectileMovement->Velocity) * speedLoss;
				projectileMovement->Velocity = bounceBackVel;

				bounceBackVel.Normalize();
				SetActorRotation(bounceBackVel.Rotation());

				hitAmount++;

				if (hitAmount >= maxHitAmount)
					Destroy();
			}
		}
	}
}

void ATT_BasicBullet::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ATT_TankBase* tank = Cast<ATT_TankBase>(OtherActor);
	if (tank && currentBulletType == EPowerupType::PT_missileBullet && owningPlayer && (OtherActor != owningPlayer))
	{
		tank->DamageTank();
		tank->DamageTank();
		Destroy();
	}
}

// Called when the game starts or when spawned
void ATT_BasicBullet::BeginPlay()
{
	Super::BeginPlay();	

	bulletMesh->OnComponentHit.AddDynamic(this, &ATT_BasicBullet::OnHit);
	overlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ATT_BasicBullet::OnOverlapBegin);
}

// Called every frame
void ATT_BasicBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATT_BasicBullet::SetupBullet(ATT_TankBase* player, EPowerupType bulletType, FRotator fireRotation)
{	
	owningPlayer = player;

	currentBulletType = bulletType;
	if (currentBulletType == EPowerupType::PT_fastBullet)
	{
		projectileMovement->Velocity = (fireRotation.Vector() * (projectileMovement->InitialSpeed * 2));
	}
	else if (currentBulletType == EPowerupType::PT_missileBullet)
	{
		projectileMovement->Velocity = (fireRotation.Vector() * (projectileMovement->InitialSpeed * 1.25));

		//UStaticMesh* meshToUse = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("StaticMesh'/Game/Assets/Bullet/Big_Missile.Big_Missile'")));
		//if (meshToUse)
		//	bulletMesh->SetStaticMesh(meshToUse);
		UMaterial* materialToUse = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("Material'/Game/Blueprints/Orange.Orange'")));
		if (materialToUse)
			bulletMesh->GetStaticMesh()->SetMaterial(0, materialToUse);

		//UParticleEmitter* emitter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion, GetActorLocation());
	}
	else if (currentBulletType == EPowerupType::PT_stunBullet)
	{
		projectileMovement->Velocity = (fireRotation.Vector() * projectileMovement->InitialSpeed);

		UMaterial* materialToUse = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("Material'/Game/Blueprints/Blue.Blue'")));
		if (materialToUse)
			bulletMesh->GetStaticMesh()->SetMaterial(0, materialToUse);

		//this bullet can travel through walls but slows down when it enters and speeds back up when it leaves the wall.
	}
	else if (currentBulletType == EPowerupType::PT_undergroundBullet)
	{
		projectileMovement->Velocity = (fireRotation.Vector() * projectileMovement->InitialSpeed);

		UMaterial* materialToUse = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("Material'/Game/Blueprints/Green.Green'")));
		if (materialToUse)
			bulletMesh->GetStaticMesh()->SetMaterial(0, materialToUse);

		//this bullet travels underground homing on the closest enemy tank.
	}
	else
	{
		projectileMovement->Velocity = (fireRotation.Vector() * projectileMovement->InitialSpeed);
	}
}