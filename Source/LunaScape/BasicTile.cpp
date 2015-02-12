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
}

//methods, move etc
//TODO
