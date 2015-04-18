// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasicTile.h"
#include "LunaScapeGameMode.h"
#include "ExitTile.generated.h"

/**
 * 
 */
UCLASS()
class LUNASCAPE_API AExitTile : public ABasicTile
{
	GENERATED_BODY()
	
public:
	AExitTile(const FObjectInitializer& ObjectInitializer);

	void OnSteppedOn();

	virtual void Tick(float DeltaSeconds) OVERRIDE;
};
