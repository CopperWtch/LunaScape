// Fill out your copyright notice in the Description page of Project Settings.

#include "LunaScape.h"
#include "LunaScapeGameMode.h"

ALunaScapeGameMode::ALunaScapeGameMode(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	//set default pawn class to the Character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Princess_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

void ALunaScapeGameMode::SetCurrentState(ELunaScapePlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(NewState);
}

void ALunaScapeGameMode::HandleNewState(ELunaScapePlayState NewState)
{
	switch (NewState)
	{
	case ELunaScapePlayState::EPlaying:
		break;
	case ELunaScapePlayState::EGameOver:
		break;
	case ELunaScapePlayState::EUnknown:
	default:
		//do nothing
		break;
	}
}