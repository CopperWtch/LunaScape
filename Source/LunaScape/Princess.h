// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Engine.h"
#include "BasicTile.h"
#include "Princess.generated.h"

/**
 * 
 */

//enum for direction the character faces
enum class EFacing : short
{
	ENorth,
	EEast,
	ESouth,
	EWest
};

UCLASS()
class LUNASCAPE_API APrincess : public ACharacter
{
	GENERATED_BODY()


public :
	APrincess(const FObjectInitializer& ObjectInitializer);
	//APrincessController pController;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Called for forwards/backward input */
	void MoveX(float Value);
	void MoveY(float Value);
	
	virtual void Tick(float DeltaSeconds) OVERRIDE;
	void CheckPath();
	TArray<AActor*> CollectedTiles;

private:
	EFacing facingDirection;
};
