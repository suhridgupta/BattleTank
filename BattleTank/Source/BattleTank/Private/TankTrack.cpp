// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	FVector ForceApplied = GetForwardVector() * FMath::Clamp<float>(Throttle, -0.5f, 0.5f) * TrackMaxDrivingForce;

	//USceneComponent is cast to UPrimitiveComponent to allow collisions to occur
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
	//Middle of the track is where the force is applied, but AddForceAtLocation is done on entire tank (can be done just on track too)
	FVector ForceLocation = GetComponentLocation();
	
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


