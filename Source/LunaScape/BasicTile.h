// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BasicTile.generated.h"

/**
 * 
 */
UCLASS()
class LUNASCAPE_API ABasicTile : public AActor
{
	GENERATED_BODY()
	
public:
	ABasicTile(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsActive;

	UPROPERTY(VisibleDefaultsOnly, BluePrintReadOnly)
	class USphereComponent* BaseCollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* TileMesh;

	/** Returns **/
	FORCEINLINE class USceneComponent* GetBaseCollisionComponent() const { return BaseCollisionComponent; }
	FORCEINLINE class USceneComponent* GetTileMesh() const { return TileMesh; }

	//methods to move them etc
	//TODO
};
