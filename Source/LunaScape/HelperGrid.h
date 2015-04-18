// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GridPlane.h"
#include "HelperGrid.generated.h"

/**
 * 
 */
UCLASS()
class LUNASCAPE_API AHelperGrid : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BPClasses)
		UClass* HelperBP;

	AHelperGrid(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsActive;

	UPROPERTY(VisibleDefaultsOnly, BluePrintReadOnly)
	class USphereComponent* BaseCollisionComponent;


	/** Returns **/
	FORCEINLINE class USceneComponent* GetBaseCollisionComponent() const { return BaseCollisionComponent; }
	
	TArray<AActor*> FloorTiles;
	FVector GetPosition();

};
