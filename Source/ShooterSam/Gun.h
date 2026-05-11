// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
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

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	UNiagaraComponent* MuzzleFlashParticleSystem;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UNiagaraSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	float BulletDamage = 10.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

};
