// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "InteractionController.generated.h"

/**
 * 
 */
UCLASS()
class LUNASCAPE_API AInteractionController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AInteractionController(const FObjectInitializer& ObjectInitializer);
	
	
};
