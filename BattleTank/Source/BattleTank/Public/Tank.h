// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above

class UTankBarrel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure,Category="Setup")
	float GetHealthPercentage() const;

	void AimAt(FVector HitLocation);

	FDeathDelegate DeathDelegate;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category="Setup")
	int32 CurrentHealth = StartingHealth;

};
