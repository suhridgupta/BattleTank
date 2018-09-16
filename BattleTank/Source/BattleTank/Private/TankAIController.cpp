// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *(PlayerTank->GetName()));
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if(!InPawn) { return; }
	ATank* AIPossessedTank = Cast<ATank>(InPawn);
	if(!ensure(AIPossessedTank)) { return; }
	AIPossessedTank->DeathDelegate.AddUniqueDynamic(this,&ATankAIController::OnPossessedTankDeath);
	//UE_LOG(LogTemp,Warning,TEXT("Death Function Added"))
}

void ATankAIController::OnPossessedTankDeath()
{
	APawn* AITankPawn = GetPawn();
	if(AITankPawn)
	{
		AITankPawn->DetachFromControllerPendingDestroy();
	}
	//UE_LOG(LogTemp,Warning,TEXT("AI Tank is Dead"))
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	// TODO Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius, true, true, false);

	// Aim towards the player
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
		
	// Fire if ready
	EFiringStatus FiringStatus = AimingComponent->GetFiringStatus();
	if(FiringStatus == EFiringStatus::Locked)
	{
		AimingComponent->Fire();
	}
}