// Team Artox

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_Shield.generated.h"

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_Shield : public AActor
{
	GENERATED_BODY()

	///////////////////
	//// VARIABLES ////
	///////////////////

	///////////////////
	//// FUNCTIONS ////
	///////////////////

public:	
	// Sets default values for this actor's properties
	ATT_Shield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
