// Fill out your copyright notice in the Description page of Project Settings.

#include "LunaScape.h"
#include "Princess.h"

APrincess::APrincess(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	//Set Size for collision capsule
	GetCapsuleComponent()->SetCapsuleSize(40.f,100.f);

	//Configure Character Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate=FRotator(0.0f, 540.0f, 0.0f);




}


