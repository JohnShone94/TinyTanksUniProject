// Team Artox


#include "TT_PowerupHolder.h"

// Sets default values
ATT_PowerupHolder::ATT_PowerupHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATT_PowerupHolder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATT_PowerupHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATT_PowerupHolder::UpdatePowerupHolder_Implementation()
{
}

