// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "ShooterAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	UE_LOG(LogTemp, Display, TEXT("Constructor of UBTService_PlayerLocationIfSeen"));
	NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UE_LOG(LogTemp, Display, TEXT("UBTService: TickNode Deltaseconds: %.5f"), DeltaSeconds);
	
	AShooterAI* ShooterAI = Cast<AShooterAI>(OwnerComp.GetAIOwner());
	AShooterSamCharacter* PlayerCharacter = ShooterAI->PlayerCharacter;
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();

	FName BlackboardKeyPlayerPos = GetSelectedBlackboardKey();
	
	if (ShooterAI && BlackBoard) {
		UE_LOG(LogTemp, Warning, TEXT("Player Position: %s"), *PlayerCharacter->GetActorLocation().ToString());

		if (ShooterAI->LineOfSightTo(PlayerCharacter)) {
			ShooterAI->SetFocus(PlayerCharacter);
			BlackBoard->SetValueAsVector(BlackboardKeyPlayerPos, PlayerCharacter->GetActorLocation());
		}
		else {
			ShooterAI->ClearFocus(EAIFocusPriority::Gameplay);
			BlackBoard->ClearValue(BlackboardKeyPlayerPos);
		}
	}
	

}
