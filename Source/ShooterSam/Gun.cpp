// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterSamCharacter.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneRoot;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SceneRoot);

	MuzzleFlashParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MuzzleFlash"));
	MuzzleFlashParticleSystem->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	if (MuzzleFlashParticleSystem)
		MuzzleFlashParticleSystem->Deactivate();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("Pulled the trigger!"));
	if (MuzzleFlashParticleSystem) {
		MuzzleFlashParticleSystem->Activate(true);
	}

	if (OwnerController) {
		FVector pointOfViewLocation;
		FRotator pointOfViewRotation;
		OwnerController->GetPlayerViewPoint(pointOfViewLocation, pointOfViewRotation);
		UE_LOG(LogTemp, Display, TEXT("Point Viewer. Location: %s, Rotation: %s"), 
			*pointOfViewLocation.ToCompactString(),
			*pointOfViewRotation.ToString());

		//AShooterSamCharacter* Character = Cast<AShooterSamCharacter>(GetOwner());
		//Character->GetCameraBoom->TargetArmLength
		FVector EndPoint = pointOfViewLocation + pointOfViewRotation.Vector() * MaxRange;

		UE_LOG(LogTemp, Display, TEXT("End Point: %s"), *EndPoint.ToCompactString());

		FHitResult HitResult;

		//if (MuzzleFlashParticleSystem) {
			//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleFlash, Mesh->GetSocketLocation(TEXT("MuzzleFlashSocket")), pointOfViewRotation);
		//}
		
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());

		bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, pointOfViewLocation,
			EndPoint, 
			ECollisionChannel::ECC_GameTraceChannel2,
			Params);

		if (IsHit) {
			if (ImpactEffect) {
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			}
			AActor* DamagedActor = HitResult.GetActor();
			if (DamagedActor) {
				UGameplayStatics::ApplyDamage(DamagedActor, BulletDamage, OwnerController, this, UDamageType::StaticClass());

			}


			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 16, FColor::Red, true);
		}

		//DrawDebugCamera(GetWorld(), pointOfViewLocation, pointOfViewRotation, 90.0f, 2.0f, FColor::Red, true);
	}
}

