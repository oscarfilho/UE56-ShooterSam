// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "ShooterSamCharacter.h"

#define LOG(x) UE_LOG(LogTemp, Display, TEXT(x))

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

void Shape::Explain() {
	LOG("I'm a shape!");
}

void Rectangle::SetSides(int32 sides) {
	Sides = sides;
}

void Rectangle::Explain() {
	LOG("I'm a rectangle!");
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	Shape shape;
	Rectangle rectangle;

	Shape* shapePtr = &shape;
	Shape* shapePtr2 = &rectangle;
	shapePtr->Explain();
	shapePtr2->Explain();

	if (MuzzleFlashParticleSystem)
		MuzzleFlashParticleSystem->Deactivate();

	//GetWorldTimerManager().SetTimer()
}



// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	if (MuzzleFlashParticleSystem) {
		MuzzleFlashParticleSystem->Activate(true);
	}

	if (OwnerController) {
		FVector pointOfViewLocation;
		FRotator pointOfViewRotation;
		OwnerController->GetPlayerViewPoint(pointOfViewLocation, pointOfViewRotation);

		AShooterSamCharacter* Character = Cast<AShooterSamCharacter>(GetOwner());

		FVector EndPoint = pointOfViewLocation + pointOfViewRotation.Vector() * MaxRange;

		DrawDebugLine(GetWorld(), pointOfViewLocation, EndPoint, FColor::Red, true, 5.0f);

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

