// Fill out your copyright notice in the Description page of Project Settings.

#include "LunaScape.h"
#include "BasicTile.h"

//constructor
ABasicTile::ABasicTile(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	//root scene component
	BaseCollisionComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));
	RootComponent = BaseCollisionComponent;

	//Create the static mesh component
	TileMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("TileMesh"));

	//create mesh and material
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	//static ConstructorHelpers::FObjectFinder<UMaterial> Material_Blue(TEXT("MaterialInstanceConstant'/Game/StarterContent/Materials/M_AssetPlatform.M_AssetPlatform'"));

	//TileMesh->SetStaticMesh(StaticMesh.Object);
	//TileMesh->SetMaterial(0, Material_Blue.Object);
	TileMesh->SetRelativeScale3D(FVector(4, 4, .25f));
	TileMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));

	//attach the static mesh component to the root component
	TileMesh->AttachTo(RootComponent);

	bIsActive = true;

	//Tick() function fires:
	PrimaryActorTick.bCanEverTick = true;
}

void ABasicTile::Tick(float DeltaSeconds)
{
	//call in constructor on after every touch even later???
	//for development in TICK

	SetNeighbours();
}

void ABasicTile::SetNeighbours()
{
	//get all actors type BasicTile that collide
	BaseCollisionComponent->GetOverlappingActors(CollectedTiles, ABasicTile::StaticClass());

	for (int32 i = 0; i < CollectedTiles.Num(); i++)
	{
		//Cast to ABasicTile
		ABasicTile* tile = Cast<ABasicTile>(CollectedTiles[i]);

		//Get positions to compare
		FVector tilePos;//= CollectedTiles[i]->GetActorLocation();
		FVector tileBounds;
		tile->GetActorBounds(false, tilePos, tileBounds);

		FVector thisPos; //= this->GetActorLocation();
		FVector thisBounds;
		this->GetActorBounds(false,thisPos,thisBounds);

		//debug
		//FString TheFloatStr = FString::SanitizeFloat(thisPos.X);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *TheFloatStr);

		//set as neighbours depending on position compared to This

		if ((tilePos.X-tileBounds.X/2)>=(thisPos.X + thisBounds.X / 2))
		{
			this->SetTileNorth(tile);
		}
		if ((tilePos.X+tileBounds.X/2) <= (thisPos.X-thisBounds.X/2))
		{
			this->SetTileSouth(tile);
		}
		if ((tilePos.Y - tileBounds.Y / 2) >= (thisPos.Y + thisBounds.Y / 2))
		{
			this->SetTileEast(tile);
		}
		if ((tilePos.Y + tileBounds.Y / 2) <= (thisPos.Y - thisBounds.Y / 2))
		{
			this->SetTileWest(tile);
		}

	}


}
//methods, move etc
//TODO
