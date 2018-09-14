// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this,&UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0.0f;
}

void UTankTrack::ApplySidewaysForce()
{
	float SlippageSpeed = FVector::DotProduct(GetRightVector(),GetComponentVelocity());

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	FVector CorrectionAcceleration = -SlippageSpeed/DeltaTime*GetRightVector();

	//USceneComponent is cast to UPrimitiveComponent to allow collisions to occur
	TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
	FVector CorrectionForce = (TankRoot->GetMass()*CorrectionAcceleration)/2; //Two Tracks

	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle += Throttle;
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle,-1.5f,1.5f);
}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;

	CurrentThrottle = 0.0f;
	
	//USceneComponent is cast to UPrimitiveComponent to allow collisions to occur
	TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	//Middle of the track is where the force is applied, but AddForceAtLocation is done on entire tank (can be done just on track too)
	FVector ForceLocation = GetComponentLocation();
	
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
