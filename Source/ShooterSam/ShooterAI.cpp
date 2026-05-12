// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"

void AShooterAI::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn) {
		SetFocus(PlayerPawn);
	}
}

//void AShooterAI::Tick(float DeltaSeconds)
//{
//	float DistanceBetween = FVector::Distance(GetPawn()->GetActorLocation(), PlayerPawn->GetActorLocation());
//	if (PlayerPawn && DistanceBetween < 1000.0f) {
//		SetFocus(PlayerPawn);
//		UE_LOG(LogTemp, Warning, TEXT("PlayerPawn is in sight. Distance: %.2f"), DistanceBetween);
//	}
//}
