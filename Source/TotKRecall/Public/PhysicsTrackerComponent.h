// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsTrackerComponent.generated.h"

USTRUCT(Blueprintable)
struct FTrackingPoint
{
	GENERATED_BODY()

	FTrackingPoint() {}
	FTrackingPoint(FVector transform, FRotator rotation) : Transform(transform), Rotation(rotation) {}

	FVector Transform;
	FRotator Rotation;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPhysicsTrackerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPhysicsTrackerComponent();
	void RequestTrackerStart();
	void RequestTrackerEnd();
	void Rewind();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	TArray<FTrackingPoint> mTransformPoints;
	bool mTrackingPhysics {false};
	bool IsRewinding { false };
	FTrackingPoint TargetStep;
	void StartTracker();
	void EndTracker();
	void GetRewindStep(FVector actorPos, FRotator actorRot, float deltaTime);
};