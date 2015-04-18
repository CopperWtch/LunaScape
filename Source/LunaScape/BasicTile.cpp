// Fill out your copyright notice in the Description page of Project Settings.

#include "LunaScape.h"
#include "BasicTile.h"
#include "LunaScapeGameMode.h"
#include "Engine.h"

//constructor
ABasicTile::ABasicTile(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	//root scene component
	BaseCollisionComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));
	RootComponent = BaseCollisionComponent;

	//Create the static mesh component
	TileMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("TileMesh"));

	//TileMesh->SetRelativeScale3D(FVector(4, 4, .25f));
	//TileMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));

	////attach the static mesh component to the root component
	TileMesh->AttachTo(RootComponent);


	bIsActive = true;
	bIsMoved= false;
	bInitialSet = false;

	//Tick() function fires:
	PrimaryActorTick.bCanEverTick = true;

	//Add Click Mechanics
	TileMesh->OnClicked.AddDynamic(this, &ABasicTile::TileClicked);
	TileMesh->OnReleased.AddDynamic(this, &ABasicTile::TileReleased);

	TileMesh->OnInputTouchBegin.AddDynamic(this, &ABasicTile::OnFingerPressedTile);
	TileMesh->OnInputTouchEnd.AddDynamic(this, &ABasicTile::OnFingerReleasedTile);



}

void ABasicTile::Tick(float DeltaSeconds)
{
	//call in constructor on after every touch even later???
	//for development in TICK

	ALunaScapeGameMode* gm = (ALunaScapeGameMode*)GetWorld()->GetAuthGameMode();
	if (gm->GetCurrentState() == ELunaScapePlayState::EPlaying)
	{
	
		if(bIsMoved)
		{
			UpdatePosition();
		}
		//if (!bInitialSet)
		//{
		//	for (TActorIterator<ABasicTile> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		//	{
		//		ABasicTile* tile = Cast<ABasicTile>(*ActorItr);
		//		tile->SetNeighbours();
		//	}
		//	bInitialSet = true;
		//}
		//SetNeighbours();
	}

	for (TActorIterator<ABasicTile> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ABasicTile* tile = Cast<ABasicTile>(*ActorItr);
		tile->SetNeighbours();
	}
}

void ABasicTile::SetNeighbours()
{


	//get all actors type BasicTile that collide
	BaseCollisionComponent->GetOverlappingActors(CollectedTiles, ABasicTile::StaticClass());

	for (int32 i = 0; i < CollectedTiles.Num(); i++)
	{
		//Cast to ABasicTile
		ABasicTile* tile = Cast<ABasicTile>(CollectedTiles[i]);

		//only set neighbour tiles if:
		//the overlapping tile isnt THIS tile & the overlapping tile isn't currently moving & THIS tile isn't currently moving!
		if (tile != this && !tile->GetIsMoved() && !bIsMoved)
		{
		
			//Get positions to compare
			FVector tilePos;//= CollectedTiles[i]->GetActorLocation();
			FVector tileBounds;
			tile->GetActorBounds(false, tilePos, tileBounds);

			FVector thisPos; //= this->GetActorLocation();
			FVector thisBounds;
			this->GetActorBounds(false,thisPos,thisBounds);

			//debug
			//FString TheFloatStr = FString::SanitizeFloat(thisPos.X);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *TheFloatStr);

			//set as neighbours depending on position compared to This
			if ((tilePos.X-tileBounds.X/2)>=(thisPos.X + thisBounds.X / 2))
			{
				this->SetTileNorth(tile);
			}
			if ((tilePos.X+tileBounds.X/2) <= (thisPos.X-thisBounds.X/2))
			{
				this->SetTileSouth(tile);
			}
			if ((tilePos.Y - tileBounds.Y / 2) >= (thisPos.Y + thisBounds.Y / 2))
			{
				this->SetTileEast(tile);
			}
			if ((tilePos.Y + tileBounds.Y / 2) <= (thisPos.Y - thisBounds.Y / 2))
			{
				this->SetTileWest(tile);
			}

			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("SET"));
		}
		/*else
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "self");*/
	}
	if (CollectedTiles.Num()==0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("NOT SET"));
	}
		


	FindPath();
}

void ABasicTile::FindPath()
{
	BaseCollisionComponent->GetOverlappingActors(CollidingActors, APrincess::StaticClass());
	if (CollidingActors.Num()>0)
	{
		princess = Cast<APrincess>(CollidingActors[0]);


		switch (princess->GetfacingDirection())
		{
		case EFacing::ENorth:
			if (!this->tileNorth &&
				this->GetActorLocation().X >= princess->GetActorLocation().X - 50 &&
				this->GetActorLocation().X <= princess->GetActorLocation().X + 50  )
			{
				if (this->tileEast)
				{
					princess->SetfacingDirection(EFacing::EEast);
					FVector pos = tileEast->GetActorLocation();
					FString xPos = FString::SanitizeFloat(pos.X);
					xPos.Append(" ");
					xPos.Append(FString::SanitizeFloat(pos.Y));
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, xPos);
				}
				else if (this->tileWest)
					princess->SetfacingDirection(EFacing::EWest);
			}
			break;
		case EFacing::EEast:
			if (!this->tileEast &&
				this->GetActorLocation().Y >= princess->GetActorLocation().Y - 50 &&
				this->GetActorLocation().Y <= princess->GetActorLocation().Y + 50)
			{
				if (this->tileSouth)
					princess->SetfacingDirection(EFacing::ESouth);
				else if (this->tileNorth)
					princess->SetfacingDirection(EFacing::ENorth);
			}
			break;
		case EFacing::ESouth:
			if (!this->tileSouth &&
				this->GetActorLocation().X >= princess->GetActorLocation().X - 50 &&
				this->GetActorLocation().X <= princess->GetActorLocation().X + 50)
			{
				if (this->tileWest)
					princess->SetfacingDirection(EFacing::EWest);
				else if (this->tileEast)
					princess->SetfacingDirection(EFacing::EEast);
			}
			break;
		case EFacing::EWest:
			if (!this->tileWest&&
				this->GetActorLocation().Y >= princess->GetActorLocation().Y - 50 &&
				this->GetActorLocation().Y <= princess->GetActorLocation().Y + 50)
			{
				if (this->tileNorth)
					princess->SetfacingDirection(EFacing::ENorth);
				else if (this->tileSouth)
					princess->SetfacingDirection(EFacing::ESouth);
			}
			break;
		default:
			break;
		}
		/*}*/
	}
}

//methods, move etc

void ABasicTile::TileClicked(UPrimitiveComponent* ClickedComp)
{
	// Check if we are not already active
	if(bIsActive)
	{
		// DO WHATEVER
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("CLICKED"));
		bIsMoved=true;
	}

	for (TActorIterator<APrincess> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		princess = Cast<APrincess>(*ActorItr);
		if (princess->GetVel() == 0)
		princess->SetVelocity(0.5f);
	}
	
	//Set this tile = NULL for neighbours
	//Set all neighbours = NULL
	if (this->tileEast)
	{
		tileEast->SetTileWest(NULL);
		FVector pos = tileEast->GetActorLocation();
		FString xPos = FString::SanitizeFloat(pos.X);
		xPos.Append(" EAST ");
		xPos.Append(FString::SanitizeFloat(pos.Y));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, xPos);

		tileEast = NULL;
	}
	if (this->tileWest)
	{
		tileWest->SetTileEast(NULL);
		FVector pos = tileWest->GetActorLocation();
		FString xPos = FString::SanitizeFloat(pos.X);
		xPos.Append(" WEST ");
		xPos.Append(FString::SanitizeFloat(pos.Y));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, xPos);

		tileWest = NULL;
	}
	if (this->tileSouth)
	{
		tileSouth->SetTileNorth(NULL);
		FVector pos = tileSouth->GetActorLocation();
		FString xPos = FString::SanitizeFloat(pos.X);
		xPos.Append(" SOUTH ");
		xPos.Append(FString::SanitizeFloat(pos.Y));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, xPos);

		tileSouth = NULL;
	}
	if (this->tileNorth)
	{
		tileNorth->SetTileSouth(NULL);
		FVector pos = tileNorth->GetActorLocation();
		FString xPos = FString::SanitizeFloat(pos.X);
		xPos.Append(" NORTH ");
		xPos.Append(FString::SanitizeFloat(pos.Y));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, xPos);

		tileNorth = NULL;
	}

}


void ABasicTile::OnFingerPressedTile(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	TileClicked(TouchedComponent);
}

void ABasicTile::TileReleased(UPrimitiveComponent* ClickedComp)
{
	bIsMoved=false;

	ALunaScapeGameMode* gm = (ALunaScapeGameMode*)GetWorld()->GetAuthGameMode();

	gm->countMoves = gm->GetNumMoves() + 1;

	int c = gm->GetNumMoves();

	FString TheFloatStr = FString::SanitizeFloat(c);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *TheFloatStr);


	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("RELEASEd"));

	for (TActorIterator<ABasicTile> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ABasicTile* tile = Cast<ABasicTile>(*ActorItr);
		tile->SetNeighbours();
	}
	//SetNeighbours();

	BaseCollisionComponent->GetOverlappingActors(CollectedTiles, ABasicTile::StaticClass());
	if (CollectedTiles.Num() > 0)
	{	
		for (int32 i = 0; i < CollectedTiles.Num(); i++)
		{
			ABasicTile* tile = Cast<ABasicTile>(CollectedTiles[i]);

			if (tile != this)
			{

				FString yPos = FString::SanitizeFloat(tile->GetActorLocation().Y);
				FString xPos = FString::SanitizeFloat(tile->GetActorLocation().X);
				xPos.Append(" ");
				xPos.Append(yPos);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, xPos);
			}

		}
		FString rYaw = FString::SanitizeFloat(CollectedTiles.Num());
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, rYaw);
	}
	


	if (this->GetTileEast())
	{
		FString rYaw = FString::SanitizeFloat(this->GetTileEast()->GetActorLocation().Y);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, rYaw);
	}
	
}

void ABasicTile::OnFingerReleasedTile(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	TileReleased(TouchedComponent);
}

void ABasicTile::UpdatePosition()
{
	//--------------------------------------------

	//TObjectIterator<APlayerController> pc;
	//if(!pc) return;

	//FViewport* v = CastChecked<ULocalPlayer>(pc->Player)->ViewportClient->Viewport;

	//FVector mouseScreenLocation= FVector(v->GetMouseX(), v->GetMouseY(), 0.f);
	//FVector mouseWorldLocation, mouseDirection;
	//pc->DeprojectMousePositionToWorld(mouseWorldLocation, mouseDirection);
	//mouseWorldLocation = mouseWorldLocation + mouseDirection * 1000;
	////mouseWorldLocation *= mouseDirection;

	//set position
	//this->SetActorLocation(FVector(mouseWorldLocation.X, mouseWorldLocation.Y, 0.f));

	//-------------------------------------------------

	//MAYBE GET POINT WHERE GROUND OBJECT IS HIT
	//UPDATE WITH THAT POSITION

	//TObjectIterator<APlayerController> pc;
	//if (!pc) return;

	//FHitResult TraceResult(ForceInit);
	//pc->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, TraceResult);

	//FString TraceString;
	//if (TraceResult.GetActor() != nullptr)
	//{
	//	TraceString += FString::Printf(TEXT("Trace Actor %s."), *TraceResult.GetActor()->GetName());
	//}
	//if (TraceResult.GetComponent() != nullptr)
	//{
	//	TraceString += FString::Printf(TEXT("Trace Comp %s."), *TraceResult.GetComponent()->GetName());
	//}
	//

	////FString rYaw = FString::SanitizeFloat(mouseDirection.Z);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TraceString);

	bool bChangePos = true;

	for (TActorIterator<AHelperGrid> HelperItr(GetWorld()); HelperItr; ++HelperItr)
	{
		FVector pos = HelperItr->GetPosition();

		for (TActorIterator<ABasicTile> TileItr(GetWorld()); TileItr; ++TileItr)
		{
			FVector tilePos = TileItr->GetActorLocation();
			if (bChangePos == true && tilePos == pos)
				bChangePos = false;
		}

		if (bChangePos)
		this->SetActorLocation(FVector(pos.X, pos.Y, 0.f));
		
	}

	SetNeighbours();
}
//TODO
