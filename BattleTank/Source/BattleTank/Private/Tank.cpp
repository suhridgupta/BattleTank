// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
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

float ATank::GetHealthPercentage() const
{
	return (float)CurrentHealth/(float)StartingHealth;
}

float ATank::TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser)
{
	FString TankName = GetName();
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints,0,CurrentHealth);
	CurrentHealth -= DamageToApply;
	if(CurrentHealth == 0)
	{
		UE_LOG(LogTemp,Warning,TEXT("%s: Dead"),*TankName)
		DeathDelegate.Broadcast();
	}
	UE_LOG(LogTemp,Warning,TEXT("%s: Damage Taken: %i Current Health: %i"),*TankName,DamageToApply,CurrentHealth)
	return DamageToApply;
}