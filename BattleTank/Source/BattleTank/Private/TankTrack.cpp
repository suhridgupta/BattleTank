// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	FString TrackName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: Throttling At %f Speed"), *TrackName, Throttle)

	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;

	//USceneComponent is cast to UPrimitiveComponent to allow collisions to occur
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
	//Middle of the track is where the force is applied, but AddForceAtLocation is done on entire tank (can be done just on track too)
	FVector ForceLocation = GetComponentLocation();
	
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


