// Fill out your copyright notice in the Description page of Project Settings.

#include "LunaScape.h"
#include "ExitTile.h"


AExitTile::AExitTile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void AExitTile::OnSteppedOn()
{
	
	ALunaScapeGameMode* gm = (ALunaScapeGameMode*)GetWorld()->GetAuthGameMode();
	gm->SetCurrentState(ELunaScapePlayState::EGameWon);
}

void AExitTile::Tick(float DeltaSeconds)
{
	//call in constructor on after every touch even later???
	//for development in TICK

	ALunaScapeGameMode* gm = (ALunaScapeGameMode*)GetWorld()->GetAuthGameMode();
	if (gm->GetCurrentState() == ELunaScapePlayState::EPlaying)
	{


		BaseCollisionComponent->GetOverlappingActors(CollidingActors, APrincess::StaticClass());
		if (CollidingActors.Num() > 0)
		{
			OnSteppedOn();
		}

		int p = 0;
		for (TActorIterator<APrincess> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			p++;
		}

		if (p == 0)
			gm->SetCurrentState(ELunaScapePlayState::EGameOver);
		//SetNeighbours();
	}
}
