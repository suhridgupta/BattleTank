// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	/*FString TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: Velocity: %f"), *TankName, Throw)*/
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we're replacing the functionality
	
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	//TODO Cross Product Always Too Low
	float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z*10;
	RightThrow = FMath::Clamp(RightThrow, -1.0f, 1.0f);
	IntendMoveForward(ForwardThrow);
	IntendMoveRight(RightThrow);
	//UE_LOG(LogTemp,Warning,TEXT("%s: Velocity: %s"),*TankName,*MoveVelocityString)
}