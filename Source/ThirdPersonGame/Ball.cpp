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


//void ABall::DisablePhysicAndCollision()
//{
//	if (IsPickedUp == false) 
//	{
//		BallMesh->SetSimulatePhysics(false);
//		BallMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//
//		IsPickedUp = true;
//	}
//}

void ABall::PickUp(AActor* Actor)
{
	if (IsPickedUp == false)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "PickUpBall");

		BallMesh->SetSimulatePhysics(false);
		BallMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);


		auto const ActorMesh = Actor->FindComponentByClass<USkeletalMeshComponent>();

		this->AttachToComponent(ActorMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "BallSocket");

		IsPickedUp = true;
	}
}

void ABall::Throw(AActor* Actor, float ThrowSpeed, float ThrowZOffset)
{
	if (IsPickedUp == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Ball throw");

		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		BallMesh->SetSimulatePhysics(true);
		BallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		/*FRotator NewRotation = Actor->GetActorRotation();
		NewRotation.Add(50, 0, 0);
		SetActorRotation(NewRotation);*/

		FVector ThrowVelocity = Actor->GetActorForwardVector() * ThrowSpeed + FVector(0.0f, 0.0f, ThrowZOffset);
		BallMesh->SetPhysicsLinearVelocity(ThrowVelocity, false);


		IsPickedUp = false;
	}
}
