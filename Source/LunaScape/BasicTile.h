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
private:

	//neighbour tiles
	ABasicTile* tileNorth;
	ABasicTile* tileSouth;
	ABasicTile* tileEast;
	ABasicTile* tileWest;
	
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

	//neighbour tiles GETTER
	ABasicTile* GetTileSouth(){ return tileSouth; };
	ABasicTile* GetTileNorth(){ return tileNorth; };
	ABasicTile* GetTileWest(){ return tileWest; };
	ABasicTile* GetTileEast(){ return tileEast; };

	//neighbour tiles SETTER
	void SetTileSouth(ABasicTile* tile){ tileSouth = tile; };
	void SetTileNorth(ABasicTile* tile){ tileNorth=tile; };
	void SetTileWest(ABasicTile* tile){ tileWest=tile; };
	void SetTileEast(ABasicTile* tile){ tileEast=tile; };

	virtual void Tick(float DeltaSeconds) OVERRIDE;

	void SetNeighbours();
	TArray<AActor*> CollectedTiles;
	//methods to move them etc
	//TODO
};
