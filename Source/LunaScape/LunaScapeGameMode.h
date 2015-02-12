// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "LunaScapeGameMode.generated.h"

/**
 * 
 */
//enum to store the current state of gameplay
enum class ELunaScapePlayState : short
{
	EPlaying,
	EGameOver,
	EUnknown
};

UCLASS()
class LUNASCAPE_API ALunaScapeGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ALunaScapeGameMode(const FObjectInitializer& ObjectInitializer);
	ELunaScapePlayState GetCurrentState() const;
	void SetCurrentState(ELunaScapePlayState NewState);


private:
	ELunaScapePlayState CurrentState;
	void HandleNewState(ELunaScapePlayState NewState);
	
	
};
