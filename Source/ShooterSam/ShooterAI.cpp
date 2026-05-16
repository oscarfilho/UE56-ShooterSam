// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAI::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ControllerPawn = GetPawn();

	if (EnemyAIBehaviorTree) {
		RunBehaviorTree(EnemyAIBehaviorTree);
	}
}
//
void AShooterAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//if (PlayerPawn && LineOfSightTo(PlayerPawn)) {
	//	SetFocus(PlayerPawn);
	//	MoveToActor(PlayerPawn, 300.0f);
	//}
	//else {
	//	ClearFocus(EAIFocusPriority::Gameplay);
	//	StopMovement();
	//}

//
//	float DistanceBetween = FVector::Distance(ControllerPawn->GetActorLocation(), PlayerPawn->GetActorLocation());
//	if (PlayerPawn && DistanceBetween < 1000.0f) {
//		SetFocus(PlayerPawn);
//		UE_LOG(LogTemp, Warning, TEXT("PlayerPawn is IN sight. Distance: %.2f"), DistanceBetween);
//	}
//	else {
//		ClearFocus(EAIFocusPriority::Gameplay);
//		UE_LOG(LogTemp, Warning, TEXT("PlayerPawn is OUT of sight. Distance: %.2f"), DistanceBetween);
//	}
}

void AShooterAI::StartBehaviorTree(AShooterSamCharacter* Player)
{
	if (EnemyAIBehaviorTree) {
		MyCharacter = Cast<AShooterSamCharacter>(GetPawn());

		if (Player) {
			PlayerCharacter = Player;
		}
		RunBehaviorTree(EnemyAIBehaviorTree);
		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
		
		if(BlackboardComponent && PlayerCharacter) {
			//BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), PlayerCharacter->GetActorLocation());
			BlackboardComponent->SetValueAsVector("StartLocation", MyCharacter->GetActorLocation());
		}
	}
}
