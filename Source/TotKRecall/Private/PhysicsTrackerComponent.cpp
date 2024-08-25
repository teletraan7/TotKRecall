// Fill out your copyright notice in the Description page of Project Settings.

#include "PhysicsTrackerComponent.h"

// Sets default values for this component's properties
UPhysicsTrackerComponent::UPhysicsTrackerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	mTransformPoints.Reserve(400);
}

void UPhysicsTrackerComponent::RequestTrackerStart()
{
	/*if (!mTrackingPhysics)
		StartTracker();*/
	mTrackingPhysics = true;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString("Tracker Started"));
}

void UPhysicsTrackerComponent::RequestTrackerEnd()
{
	/*if (mTrackingPhysics)
	{
		EndTracker();
	}*/
	mTrackingPhysics = false;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString("Tracker Ended"));
}

//Need to modify so it lerps between the points smoothly over a duration. Right now it just appears to jump because it executes so fast.
void UPhysicsTrackerComponent::Rewind()
{
	IsRewinding = true;
	while (mTransformPoints.Num() > 0)
	{
		FTrackingPoint point = mTransformPoints.Pop();
		GetOwner()->SetActorLocation(point.Transform, true);
		GetOwner()->SetActorRotation(point.Rotation);
	}
	IsRewinding = false;
}

void UPhysicsTrackerComponent::StartTracker()
{
	if (!IsRewinding)
	{
		mTrackingPhysics = true;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString("Tracker Started"));
	}
}

void UPhysicsTrackerComponent::EndTracker()
{
	if (!IsRewinding)
	{
		mTrackingPhysics = false;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString("Tracker Ended"));
	}
}


// Called when the game starts
void UPhysicsTrackerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPhysicsTrackerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (mTrackingPhysics)
	{
		FTrackingPoint point;
		point.Transform = GetOwner()->GetActorLocation();
		point.Rotation = GetOwner()->GetActorRotation();
		mTransformPoints.Push(point);
		if (mTransformPoints.Num() >= 400)
		{
			mTransformPoints.RemoveAt(0);
		}
	}
	for (auto point : mTransformPoints)
	{
		DrawDebugPoint(GetWorld(), point.Transform, 10, FColor::Green, false, 0.1f, 1);
	}
}

