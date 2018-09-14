// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this,&UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

	float SlippageSpeed = FVector::DotProduct(GetRightVector(),GetComponentVelocity());

	FVector CorrectionAcceleration = -SlippageSpeed/DeltaTime*GetRightVector();

	//USceneComponent is cast to UPrimitiveComponent to allow collisions to occur
	TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
	FVector CorrectionForce = (TankRoot->GetMass()*CorrectionAcceleration)/2; //Two Tracks

	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	FVector ForceApplied = GetForwardVector() * FMath::Clamp<float>(Throttle, -0.5f, 0.5f) * TrackMaxDrivingForce;
	
	//USceneComponent is cast to UPrimitiveComponent to allow collisions to occur
	TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	//Middle of the track is where the force is applied, but AddForceAtLocation is done on entire tank (can be done just on track too)
	FVector ForceLocation = GetComponentLocation();
	
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp,Warning,TEXT("Generating Hit Events"))
}
