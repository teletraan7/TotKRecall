// Fill out your copyright notice in the Description page of Project Settings.

#include "PhysicsTrackerComponent.h"

#include <string>

// Sets default values for this component's properties
UPhysicsTrackerComponent::UPhysicsTrackerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	mTransformPoints.Reserve(400);
	
	LerpProgress = 0;
}

void UPhysicsTrackerComponent::RequestTrackerStart()
{
	if (!IsRewinding)
	{
		mTrackingPhysics = true;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString("Tracker Started"));
	}
}

void UPhysicsTrackerComponent::RequestTrackerEnd()
{
	if (!IsRewinding)
	{
		mTrackingPhysics = false;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString("Tracker Ended"));
	}
}

//Need to modify so it lerps between the points smoothly over a duration. Right now it just appears to jump because it executes so fast.
void UPhysicsTrackerComponent::Rewind()
{
	IsRewinding = true;
	TargetStep = mTransformPoints.Pop();
	//TargetStep = mTransformPoints[0];
}

void UPhysicsTrackerComponent::GetRewindStep(FVector actorPos, FRotator actorRot, float deltaTime)
{
	//get distance between current position and target
	//FVector sum = actorPos - TargetStep.Transform;
	//float distance = sum.Length();
	//if distance is below threshold then pop next target step
	GetOwner()->SetActorLocation(FMath::Lerp(actorPos, TargetStep.Transform, LerpProgress));
	GetOwner()->SetActorRotation(FMath::Lerp(actorRot, TargetStep.Rotation, LerpProgress));
	if (LerpProgress >= 1)
	{
		//GetOwner()->SetActorLocation(TargetStep.Transform);
		//GetOwner()->SetActorRotation(TargetStep.Rotation);
		LerpProgress = 0;
		if (mTransformPoints.Num() == 0)
		{
			IsRewinding = false;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, FString("Lerp finished"));
		}
		else
		{
			TargetStep = mTransformPoints.Pop();
		}
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

	if (mTrackingPhysics && !IsRewinding)
	{
		FTrackingPoint point { GetOwner()->GetActorLocation() , GetOwner()->GetActorRotation() };
		mTransformPoints.Push(point);
		if (mTransformPoints.Num() > 400)
		{
			mTransformPoints.RemoveAt(0);
		}
	}
	if (IsRewinding)
	{
		/*for (auto point : mTransformPoints)
		{
			DrawDebugPoint(GetWorld(), point.Transform, 10, FColor::Green, false, 0.1f, 1);
		}*/
		if (LerpProgress < 1)
		{
			LerpProgress += DeltaTime * 50;
		}
		if (LerpProgress >= 1)
		{
			LerpProgress = 1;
		}
		GetRewindStep(GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), DeltaTime);
		FString lerpString = FString::SanitizeFloat(LerpProgress);
		GEngine->AddOnScreenDebugMessage(-2, 1.0f, FColor::Magenta, *lerpString);
	}
	
}

