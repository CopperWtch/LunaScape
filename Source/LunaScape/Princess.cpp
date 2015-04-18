// Fill out your copyright notice in the Description page of Project Settings.

#include "LunaScape.h"
#include "Princess.h"
#include "LunaScapeGameMode.h"

APrincess::APrincess(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	//Set Size for collision capsule
	GetCapsuleComponent()->SetCapsuleSize(40.f,100.f);

	//Configure Character Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate=FRotator(0.0f, 540.0f, 0.0f);

	BaseTurnRate = 45.0f;

	//set the FACING variable default
	facingDirection = EFacing::ENorth;

	//starting speed:
	vel=0.f;

	//Tick() function fires:
	PrimaryActorTick.bCanEverTick = true;


}


void APrincess::MoveX(float Value)
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


void APrincess::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ALunaScapeGameMode* gm = (ALunaScapeGameMode*)GetWorld()->GetAuthGameMode();

	//Only check the path & Move if the player is playing a level
	if(gm!= NULL && gm->GetCurrentState()==ELunaScapePlayState::EPlaying)
	{

	//CheckPath();

	/*FString rYaw = FString::SanitizeFloat(this->GetActorLocation().X);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, rYaw);*/

	MoveX(vel);
	}

	
}

//void APrincess::CheckPath()
//{
//	CapsuleComponent->GetOverlappingActors(CollectedTiles, AExitTile::StaticClass());
//	if (CollectedTiles.Num()>0)
//	{
//		ALunaScapeGameMode* gm = (ALunaScapeGameMode*)GetWorld()->GetAuthGameMode();
//		gm->SetCurrentState(ELunaScapePlayState::EGameWon);
//	}
//	else
//	{
//		//get all actors type BasicTile that collide
//		CapsuleComponent->GetOverlappingActors(CollectedTiles, ABasicTile::StaticClass());
//
//		//Check if something is colliding
//		if (CollectedTiles.Num()>0)
//		{
//			//Cast to ABasicTile
//			//Only use the first tile
//			ABasicTile* tile = Cast<ABasicTile>(CollectedTiles[0]);
//
//			//Check which direction the character is facing 
//			//use the information to determine how the character needs to behave
//			switch (facingDirection)
//			{
//				//Character faces north
//			case EFacing::ENorth:
//
//				break;
//			case EFacing::EEast:
//
//				break;
//			case EFacing::ESouth:
//
//				break;
//			case EFacing::EWest:
//
//				break;
//			default:
//				break;
//			}
//		}
//		else
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "P_GAME OVER");
//			ALunaScapeGameMode* gm = (ALunaScapeGameMode*)GetWorld()->GetAuthGameMode();
//			gm->SetCurrentState(ELunaScapePlayState::EGameOver);
//		}
//	}
//}

void APrincess::SetfacingDirection(EFacing state)
{
	FRotator currentRot = Controller->GetControlRotation();
	switch (state)
	{
	case EFacing::ENorth:
		Controller->SetControlRotation(FRotator(currentRot.Pitch,0.f,currentRot.Roll));
		this->facingDirection = EFacing::ENorth;
		break;
	case EFacing::EEast:
		Controller->SetControlRotation(FRotator(currentRot.Pitch, 90.f, currentRot.Roll));
		this->facingDirection = EFacing::EEast;
		break;
	case EFacing::ESouth:
		Controller->SetControlRotation(FRotator(currentRot.Pitch, 180.f, currentRot.Roll));
		this->facingDirection = EFacing::ESouth;
		break;
	case EFacing::EWest:
		Controller->SetControlRotation(FRotator(currentRot.Pitch, -90.f, currentRot.Roll));
		this->facingDirection = EFacing::EWest;
		break;
	default:
		break;
	}

	
}