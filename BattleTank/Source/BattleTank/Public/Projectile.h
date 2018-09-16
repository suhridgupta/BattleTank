// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float DestroyDelay = 5.0f;

public:	
	void LaunchProjectile(float Speed);

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UProjectileMovementComponent* ProjectileMovement = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category="Setup")
	UStaticMeshComponent *CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category="Setup")
	UParticleSystemComponent *LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category="Setup")
	UParticleSystemComponent *ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category="Setup")
	URadialForceComponent* ExplosionForce = nullptr;

	void OnTimerExpire();
};
