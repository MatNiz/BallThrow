// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPool.generated.h"

UCLASS()
class THIRDPERSONGAME_API AObjectPool : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObjectPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	void Initialize(TSubclassOf<AActor> ActorClass, int InitialSize);

	AActor* GetObject();

	void ReturnObject(AActor* ObjectToReturn);


private:
	TSubclassOf<AActor> ObjectClass;
	TArray<AActor*> ObjectPool;
	int PoolSize;


};
