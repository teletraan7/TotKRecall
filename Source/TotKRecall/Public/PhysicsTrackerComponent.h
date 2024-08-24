// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSStack.h"
#include "Components/ActorComponent.h"
#include "PhysicsTrackerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPhysicsTrackerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPhysicsTrackerComponent();
	void RequestTrackerStart();
	void RequestTrackerEnd();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/*TUniquePtr<FSStack> mPhysicsStack;
	FSStack mTransformStack;
	uint16_t mPhysicsPoint {40};*/
	TArray<FVector> mTransformPoints;
	bool mTrackingPhysics {false};
	void StartTracker();
	void EndTracker();
};