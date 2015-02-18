// Fill out your copyright notice in the Description page of Project Settings.

#include "LunaScape.h"
#include "BTTask_FindLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


UBTTask_FindLocation::UBTTask_FindLocation(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP)
{

}

EBTNodeResult::Type UBTTask_FindLocation::ExecuteTask(class UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory)
{
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(OwnerComp);
	AAIController* MyAI = Cast<AAIController>(OwnerComp->GetOwner());
	if (NavSys && MyAI && MyAI->GetPawn())
	{
		const float SearchRadius = 10.0f;
		FNavLocation RandomPt;

		const bool bFound = NavSys->GetRandomPointInRadius(MyAI->GetPawn()->GetActorLocation(), SearchRadius, RandomPt);
		if (bFound)
		{
			OwnerComp->GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), RandomPt.Location);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}


