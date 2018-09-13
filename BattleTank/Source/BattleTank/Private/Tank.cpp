// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect points as added at construction
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

//// Called to bind functionality to input
//void ATank::SetupPlayerInputComponent(class UInputComponent* inputComponent)
//{
//	Super::SetupPlayerInputComponent(inputComponent);
//
//}

void ATank::Fire()
{
	float CurrentTime = GetWorld()->GetTimeSeconds();
	bool isReloaded = (CurrentTime - LastFireTime) > ReloadTimeInSeconds;
	if (!ensure(Barrel)) { return; }
	// Spawn a projectile at the socket location on the barrel
	if (Barrel && isReloaded)
	{
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = CurrentTime;
	}
}
