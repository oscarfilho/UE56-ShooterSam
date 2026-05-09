// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneRoot;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("Pulled the trigger!"));
	if (OwnerController) {
		FVector pointOfViewLocation;
		FRotator pointOfViewRotation;
		OwnerController->GetPlayerViewPoint(pointOfViewLocation, pointOfViewRotation);
		UE_LOG(LogTemp, Display, TEXT("Point Viewer. Location: %s, Rotation: %s"), 
			*pointOfViewLocation.ToCompactString(),
			*pointOfViewRotation.ToString());

		DrawDebugCamera(GetWorld(), pointOfViewLocation, pointOfViewRotation, 90.0f, 2.0f, FColor::Red, true);
	}
}

