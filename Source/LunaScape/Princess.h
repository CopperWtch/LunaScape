// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Engine.h"

#include "Princess.generated.h"

/**
 * 
 */
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
	void MoveForward(float Value);

	//Called to turn 
	void TurnAtRate(float Rate);
	
	virtual void Tick(float DeltaSeconds) OVERRIDE;
};
