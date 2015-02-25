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
	SetCurrentState(ELunaScapePlayState::EMenu);

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
		if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "EPlaying");
		break;
	case ELunaScapePlayState::EGameOver:
		if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "EGameOver");
		break;
	case ELunaScapePlayState::EGameWon:
		if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "EGameWon");
		break;
	case ELunaScapePlayState::EMenu:
		if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "EMenu");
		break;
	case ELunaScapePlayState::EUnknown:
		if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "EUnknown");
	default:
		//do nothing
		break;
	}
}