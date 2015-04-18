// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "LunaScapeGameMode.generated.h"

/**
 * 
 */
//enum to store the current state of gameplay
 UENUM(BlueprintType)
enum class ELunaScapePlayState : uint8 //short
{
	EPlaying			UMETA(DisplayName="EPlaying"),
	EGameOver			UMETA(DisplayName="EGameOver"),
	EGameWon			UMETA(DisplayName="EGameWon"),
	EMenu				UMETA(DisplayName="EMenu"),
	EUnknown			UMETA(DisplayName="EUnknown")
};

UCLASS()
class LUNASCAPE_API ALunaScapeGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ALunaScapeGameMode(const FObjectInitializer& ObjectInitializer);
	ELunaScapePlayState GetCurrentState() const;

	UFUNCTION(BlueprintCallable, Category="Enum")
	void SetCurrentState(ELunaScapePlayState NewState);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Enum)
	ELunaScapePlayState CurrentState;

	/** amount of moves */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NumberOfMoves)
		int32 countMoves;

private:

	void HandleNewState(ELunaScapePlayState NewState);

public:
	UFUNCTION(BlueprintCallable, Category = "NumberOfMoves")
		int32 GetNumMoves(){ return countMoves; };
	
	
};
FORCEINLINE ELunaScapePlayState ALunaScapeGameMode::GetCurrentState() const
{
	return CurrentState;
}
