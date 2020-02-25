// Team Artox

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TT_TankBase.h"
#include "TT_PowerupHolder.generated.h"

UCLASS()
class TINYTANKSUNIPROJECT_API ATT_PowerupHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATT_PowerupHolder();

	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly)
		ATT_TankBase* owningTank;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Category = "Powerup Holder", BlueprintCallable)
		void SetOwningTank(ATT_TankBase* tank) { owningTank = tank; };

	UFUNCTION(Category = "Powerup Holder", BlueprintPure)
		ATT_TankBase* GetOwningTank() { return owningTank;	};

	UFUNCTION(Category = "Powerup Holder", BlueprintNativeEvent)
		void UpdatePowerupHolder();

	virtual void UpdatePowerupHolder_Implementation();

};
