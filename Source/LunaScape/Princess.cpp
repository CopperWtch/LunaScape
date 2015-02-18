// Fill out your copyright notice in the Description page of Project Settings.

#include "LunaScape.h"
#include "Princess.h"

APrincess::APrincess(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("I Worked!"));
	//}

	//Set Size for collision capsule
	GetCapsuleComponent()->SetCapsuleSize(40.f,100.f);

	//Configure Character Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate=FRotator(0.0f, 540.0f, 0.0f);

	BaseTurnRate = 45.0f;


	//Tick() function fires:
	PrimaryActorTick.bCanEverTick = true;


}


void APrincess::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APrincess::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APrincess::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	MoveForward(0.3f);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "CHAR TICK");

}