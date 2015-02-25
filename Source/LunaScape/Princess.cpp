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
	vel=5.f;

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

void APrincess::MoveY(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
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

	CheckPath();

	FString rYaw = FString::SanitizeFloat(this->GetControlRotation().Yaw);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, rYaw);
	}

	//velocity=velocity*velocity;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "CHAR TICK");

}

//Checks where to go according to the positions of the tiles
void APrincess::CheckPath()
{
	CapsuleComponent->GetOverlappingActors(CollectedTiles, AExitTile::StaticClass());
	if(CollectedTiles.Num()>0)
		{
			ALunaScapeGameMode* gm = (ALunaScapeGameMode*)GetWorld()->GetAuthGameMode();
			gm->SetCurrentState(ELunaScapePlayState::EGameWon);
		}
	else
	{
	//get all actors type BasicTile that collide
	CapsuleComponent->GetOverlappingActors(CollectedTiles, ABasicTile::StaticClass());

	//Check if something is colliding
	if (CollectedTiles.Num()>0)
	{
		//Cast to ABasicTile
		//Only use the first tile
		ABasicTile* tile = Cast<ABasicTile>(CollectedTiles[0]);

		//Check which direction the character is facing 
		//use the information to determine how the character needs to behave
		switch (facingDirection)
		{
			//Character faces north
		case EFacing::ENorth:
			MoveX(vel);
			if (tile->GetTileNorth())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "FORWARD");
				
			}
			else if (tile->GetTileEast())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "TURN RIGHT");


				const FRotator Rotation = Controller->GetControlRotation();
				AddControllerYawInput(+35);

				facingDirection = EFacing::EEast;
			}
			else if (tile->GetTileWest())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "TURN LEFT");
				
				const FRotator Rotation = Controller->GetControlRotation();
				AddControllerYawInput( - 35);

				facingDirection = EFacing::EWest;
			}
			break;
		case EFacing::EEast:
			//Character faces EAST
			MoveX(vel);
			if (tile->GetTileEast())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "FORWARD");
				
			}
			else if (tile->GetTileSouth())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "TURN RIGHT");

				const FRotator Rotation = Controller->GetControlRotation();
				AddControllerYawInput(+ 35);
				facingDirection = EFacing::ESouth;
			}
			else if (tile->GetTileNorth())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "TURN LEFT");
				const FRotator Rotation = Controller->GetControlRotation();
				AddControllerYawInput( - 35);
				facingDirection = EFacing::ENorth;
			}
			break;
		case EFacing::ESouth:
			//Character faces SOUTH
			MoveX(vel);
			if (tile->GetTileSouth())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "FORWARD");
				
			}
			else if (tile->GetTileWest())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "TURN RIGHT");

				const FRotator Rotation = Controller->GetControlRotation();
				AddControllerYawInput(+ 35);
				facingDirection = EFacing::EWest;
			}
			else if (tile->GetTileEast())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "TURN LEFT");
				const FRotator Rotation = Controller->GetControlRotation();
				AddControllerYawInput(- 35);
				facingDirection = EFacing::EEast;
			}
			break;
		case EFacing::EWest:
			//Character faces WEST
			MoveX(vel);
			if (tile->GetTileWest())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "FORWARD");
				
			}
			else if (tile->GetTileNorth())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "TURN RIGHT");

				const FRotator Rotation = Controller->GetControlRotation();
				AddControllerYawInput(+ 35);
				facingDirection = EFacing::ENorth;
			}
			else if (tile->GetTileSouth())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "TURN LEFT");
				const FRotator Rotation = Controller->GetControlRotation();
				AddControllerYawInput(- 35);
				facingDirection = EFacing::ESouth;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "P_GAME OVER");
		ALunaScapeGameMode* gm = (ALunaScapeGameMode*)GetWorld()->GetAuthGameMode();
		gm->SetCurrentState(ELunaScapePlayState::EGameOver);
	}
	}
}