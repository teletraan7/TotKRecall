// Fill out your copyright notice in the Description page of Project Settings.


#include "TackingStaticMeshActor.h"

// Sets default values
ATackingStaticMeshActor::ATackingStaticMeshActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = mStaticMesh;
	mPhysicsTracker =  CreateDefaultSubobject<UPhysicsTrackerComponent>("PhysicsTracker");
	mPhysicsTracker->RegisterComponent(); //Had to register to get component tick to work.
}

// Called when the game starts or when spawned
void ATackingStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();
	mStaticMesh->SetSimulatePhysics(true);
	mStaticMesh->OnComponentWake.AddDynamic(this, &ATackingStaticMeshActor::OnPhysicsStateAwake);
	mStaticMesh->OnComponentSleep.AddDynamic(this, &ATackingStaticMeshActor::OnPhysicsStateSleep);
}

void ATackingStaticMeshActor::OnPhysicsStateAwake(UPrimitiveComponent* ChangedComponent, FName name)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString("Physics Awake"));
	mPhysicsTracker->RequestTrackerStart();
}

void ATackingStaticMeshActor::OnPhysicsStateSleep(UPrimitiveComponent* ChangedComponent, FName name)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString("Physics Sleeping"));
	mPhysicsTracker->RequestTrackerEnd();
}

void ATackingStaticMeshActor::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//mPhysicsTracker->RequestTrackerStart();
}

// Called every frame
void ATackingStaticMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

