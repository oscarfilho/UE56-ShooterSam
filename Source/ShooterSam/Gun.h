// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundBase.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTERSAM_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

public:
	UPROPERTY(EditAnywhere, Category="Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, Category="Components")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	AController* OwnerController;

	UPROPERTY(EditAnywhere, Category = "Gun")
	float MaxRange = 1000.0f;

	UPROPERTY(VisibleAnywhere, Category = "Gun Effects")
	UNiagaraComponent* MuzzleFlashParticleSystem;

	UPROPERTY(EditAnywhere, Category = "Gun Effects")
	UNiagaraSystem* ImpactEffect;

	UPROPERTY(EditAnywhere, Category = "Gun")
	float BulletDamage = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Gun")
	USoundBase* ShootSound;

	UPROPERTY(EditAnywhere, Category = "Gun")
	USoundBase* ImpactSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

};


class Shape {
protected:
	int32 Sides;

public:
	virtual void Explain();
};


class Rectangle : public Shape {
public:
	void SetSides(int32 sides);
	void Explain() override;
};