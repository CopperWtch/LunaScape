// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Princess.h"
#include "HelperGrid.h"
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

	//Is the Tile currently being moved?
	bool bIsMoved;
	bool bInitialSet;
	
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
	//FORCEINLINE class USceneComponent* GetTileMesh() const { return TileMesh; }

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
	TArray<AActor*> CloseTiles;

	//methods to move them etc--------------------------------------------------------------------------------------

	bool GetIsMoved(){ return bIsMoved;	};
	void SetIsMoved(bool value){bIsMoved = value;};

	/** Handle the block being clicked */
	UFUNCTION()
	void TileClicked(UPrimitiveComponent* ClickedComp);

	/** Handle the block being released */
	UFUNCTION()
	void TileReleased(UPrimitiveComponent* ClickedComp);

	/** Handle the block being touched  */
	UFUNCTION()
	void OnFingerPressedTile(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	/** Handle the block being released  */
	UFUNCTION()
	void OnFingerReleasedTile(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	//Update position of the tile when dragged
	UFUNCTION()
	void UpdatePosition();

	APrincess* princess;
	TArray<AActor*> CollidingActors;
	void FindPath();
	//TODO
};
