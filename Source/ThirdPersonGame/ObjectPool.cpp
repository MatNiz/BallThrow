// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool.h"

// Sets default values
AObjectPool::AObjectPool()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectPool::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AObjectPool::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AObjectPool::Initialize(TSubclassOf<AActor> ActorClass, int InitialSize)
{
    ObjectClass = ActorClass;
    PoolSize = InitialSize;

    for (int i = 0; i < PoolSize; ++i)
    {
        AActor* NewObject = GetWorld()->SpawnActor<AActor>(ObjectClass, FVector(0, 0, 500), FRotator::ZeroRotator);
        if (NewObject)
        {
            NewObject->SetActorHiddenInGame(true);
            ObjectPool.Add(NewObject);
        }
    }
}

AActor* AObjectPool::GetObject()
{
    // ZnajdŸ i zwróæ nieaktywny obiekt z puli
    for (AActor* Object : ObjectPool)
    {
        if (!Object->IsActorBeingDestroyed() && Object->IsHidden())
        {
            Object->SetActorHiddenInGame(false);
            return Object;
        }
    }

    // Jeœli brak dostêpnych obiektów, zwróæ nullptr lub stwórz nowy obiekt
    AActor* NewObject = GetWorld()->SpawnActor<AActor>(ObjectClass, FVector::ZeroVector, FRotator::ZeroRotator);
    if (NewObject)
    {
        NewObject->SetActorHiddenInGame(false);
        ObjectPool.Add(NewObject);
        return NewObject;
    }

    return nullptr;
}

void AObjectPool::ReturnObject(AActor* ObjectToReturn)
{
    if (ObjectToReturn && !ObjectToReturn->IsActorBeingDestroyed())
    {
        ObjectToReturn->SetActorHiddenInGame(true);
    }
}

