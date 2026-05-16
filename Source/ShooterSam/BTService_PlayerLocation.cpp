// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "ShooterAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = "Get Player Location";
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	AShooterAI* OwnerController = Cast<AShooterAI>(OwnerComp.GetAIOwner());
	UBlackboardComponent* Blackboard = OwnerController->GetBlackboardComponent();
	AShooterSamCharacter* Player = OwnerController->PlayerCharacter;

	if (OwnerController && Blackboard && Player) {
		Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
	}

}
