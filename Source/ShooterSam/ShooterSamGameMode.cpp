// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSamGameMode.h"
#include "ShooterSamCharacter.h"
#include "ShooterAI.h"

AShooterSamGameMode::AShooterSamGameMode()
{
	// stub
}

void AShooterSamGameMode::BeginPlay()
{
	Super::BeginPlay();
	AShooterSamCharacter* Player = Cast<AShooterSamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	TArray<AActor*> ShooterAIs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), ShooterAIs);
	
	for (AActor* AEnemyAI : ShooterAIs) {
		AShooterAI* EnemyAI = Cast<AShooterAI>(AEnemyAI);
		if (EnemyAI) {
			EnemyAI->StartBehaviorTree(Player);
			UE_LOG(LogTemp, Display, TEXT("Actor name %s started behavior tree."), *EnemyAI->GetActorNameOrLabel());
		}
	}
}