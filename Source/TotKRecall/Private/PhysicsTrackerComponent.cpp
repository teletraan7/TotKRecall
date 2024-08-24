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

void UPhysicsTrackerComponent::StartTracker()
{
	mTrackingPhysics = true;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString("Tracker Started"));
}

void UPhysicsTrackerComponent::EndTracker()
{
	mTrackingPhysics = false;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString("Tracker Ended"));
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
		FVector test = GetOwner()->GetActorLocation();
		mTransformPoints.Push(test);
		if (mTransformPoints.Num() >= 400)
		{
			mTransformPoints.RemoveAt(0);
		}
	}
	for (auto point : mTransformPoints)
	{
		DrawDebugPoint(GetWorld(), point, 10, FColor::Green, false, 0.1f, 1);
	}
}

