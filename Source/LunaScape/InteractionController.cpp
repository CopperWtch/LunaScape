// Fill out your copyright notice in the Description page of Project Settings.

#include "LunaScape.h"
#include "InteractionController.h"

AInteractionController::AInteractionController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}



