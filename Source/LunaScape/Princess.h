// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
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

//protected:
	// APawn interface
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	
	
};
