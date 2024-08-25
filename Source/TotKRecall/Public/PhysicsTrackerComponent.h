// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsTrackerComponent.generated.h"

USTRUCT()
struct FTrackingPoint
{
	GENERATED_BODY()

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
	void StartTracker();
	void EndTracker();
};