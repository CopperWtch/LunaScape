// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GridPlane.generated.h"

/**
 * 
 */
UCLASS()
class LUNASCAPE_API AGridPlane : public AActor
{
	GENERATED_BODY()

public:
	AGridPlane(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsActive;

	UPROPERTY(VisibleDefaultsOnly, BluePrintReadOnly)
	class USphereComponent* BaseCollisionComponent;

	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	//class UStaticMeshComponent* TileMesh;

	/** Returns **/
	FORCEINLINE class USceneComponent* GetBaseCollisionComponent() const { return BaseCollisionComponent; }
	/*FORCEINLINE class USceneComponent* GetTileMesh() const { return TileMesh; }*/
	
};
