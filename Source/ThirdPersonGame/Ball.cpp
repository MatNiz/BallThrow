// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>("BallMesh");
	RootComponent = BallMesh;

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABall::DisablePhysicAndCollision(AActor* Actor)
{
	if (IsPickedUp == false) 
	{
		BallMesh->SetSimulatePhysics(false);
		BallMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		//AttachToActor(Actor, FAttachmentTransformRules::SnapToTargetIncludingScale);
		IsPickedUp = true;
	}
}


void ABall::Throw(AActor* Actor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Ball throw");

	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	FVector ThrowVelocity = Actor->GetActorForwardVector() * ThrowSpeed + FVector(0.0f, 0.0f, 800.0f);
	BallMesh->SetPhysicsLinearVelocity(ThrowVelocity, false);

	IsPickedUp = false;

}