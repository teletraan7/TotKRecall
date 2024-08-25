// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsTrackerComponent.h"
#include "TackingStaticMeshActor.generated.h"

UCLASS(config = Game)
class ATackingStaticMeshActor : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATackingStaticMeshActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mStaticMesh;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION() //Must make ufunction to work with binding later.
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION() //Must make ufunction to work with binding later.
	void OnPhysicsStateAwake(UPrimitiveComponent* ChangedComponent, FName name);
	UFUNCTION() //Must make ufunction to work with binding later.
	void OnPhysicsStateSleep(UPrimitiveComponent* ChangedComponent, FName name);
	UPhysicsTrackerComponent* mPhysicsTracker;
	virtual void Interact() override;
};
