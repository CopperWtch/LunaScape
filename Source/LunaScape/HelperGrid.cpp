// Fill out your copyright notice in the Description page of Project Settings.

#include "LunaScape.h"
#include "HelperGrid.h"

AHelperGrid::AHelperGrid(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	//root scene component
	BaseCollisionComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));
	RootComponent = BaseCollisionComponent;

	
}

void AHelperGrid::BeginPlay()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			float posX = i * 400;
			float posY = j * 400;
			AGridPlane* tile = GetWorld()->SpawnActor<AGridPlane>(HelperBP, FVector(posX, posY, -20.f), FRotator(0, 0, 0));
		}
	}
}

FVector AHelperGrid::GetPosition()
{
	FVector position;

	//MAYBE GET POINT WHERE GROUND OBJECT IS HIT
	//UPDATE WITH THAT POSITION

	TObjectIterator<APlayerController> pc;
	if (pc)
	{

		FHitResult TraceResult(ForceInit);
		pc->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, TraceResult);

		//FString TraceString;
		if (TraceResult.GetActor() != nullptr)
		{
			position = TraceResult.GetActor()->GetActorLocation();
		}
		//if (TraceResult.GetComponent() != nullptr)
		//{
		//	TraceString += FString::Printf(TEXT("Trace Comp %s."), *TraceResult.GetComponent()->GetName());
		//}
		//

		////FString rYaw = FString::SanitizeFloat(mouseDirection.Z);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TraceString);
	}


	return position;
}

