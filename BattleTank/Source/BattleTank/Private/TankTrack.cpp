// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	FString TrackName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: Throttling At %f Speed"), *TrackName, Throttle)
}


