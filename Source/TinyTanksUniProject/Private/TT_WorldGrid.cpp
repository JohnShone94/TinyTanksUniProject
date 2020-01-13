// Fill out your copyright notice in the Description page of Project Settings.


#include "TT_WorldGrid.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"

ATT_WorldGrid::ATT_WorldGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("The Box"));
	RootComponent = box;
}

void ATT_WorldGrid::BeginPlay()
{
	Super::BeginPlay();

}

void ATT_WorldGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#if WITH_EDITOR
void ATT_WorldGrid::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if ((PropertyName == GET_MEMBER_NAME_CHECKED(ATT_WorldGrid, cellSizeX)) || (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_WorldGrid, cellSizeY)) || (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_WorldGrid, gridSizeX)) || (PropertyName == GET_MEMBER_NAME_CHECKED(ATT_WorldGrid, gridSizeY)))
	{
		box->SetBoxExtent(FVector(cellSizeX, cellSizeY, 10.0f));
		
		if (cellArray.Num() > 0)
		{
			for (int i = 0; i < cellArray.Num(); i++)
			{
				if(cellArray[i])
					cellArray[i]->DestroyComponent();
			}

			cellArray.Empty();
		}

		FVector startVector = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
		for (int x = 2; x <= gridSizeX; x++)
		{
			for (int y = 2; y <= gridSizeY; y++)
			{
				UBoxComponent* cell = NewObject<UBoxComponent>(this, UBoxComponent::StaticClass());
				cell->RegisterComponent();
				cell->SetupAttachment(RootComponent);
				cell->SetRelativeLocation(FVector((startVector.X + (cellSizeX * x)), (startVector.Y + (cellSizeY * y)), startVector.Z)); 
				cell->SetBoxExtent(FVector(cellSizeX, cellSizeY, 10.0f));
				cellArray.Add(cell);
			}
		}
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
