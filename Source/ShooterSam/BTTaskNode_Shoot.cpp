// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"
#include "ShooterSamCharacter.h"
#include "ShooterAI.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	AShooterAI* ShooterAI = Cast<AShooterAI>(OwnerComp.GetAIOwner());
	if (ShooterAI) {
		AShooterSamCharacter* Player = ShooterAI->MyCharacter;
		if (Player && Player->IsAlive) {
			Player->DoShoot();
			Result = EBTNodeResult::Succeeded;
		}
	}
	return Result;
}
