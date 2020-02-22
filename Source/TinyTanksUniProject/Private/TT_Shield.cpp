// Team Artox


#include "TT_Shield.h"

// Sets default values
ATT_Shield::ATT_Shield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATT_Shield::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATT_Shield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

