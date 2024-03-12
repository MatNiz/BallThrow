// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chest.generated.h"

UCLASS()
class BALLTHROW_API AChest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void ChestInteracton();
	bool GetChestStateBool();

private:
	UPROPERTY(EditDefaultsOnly, Category = "References")
		TSubclassOf<class ABall> BallClass;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
		class UStaticMeshComponent* ChestMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	class UStaticMesh* ChestClosedMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	class UStaticMesh* ChestOpenMesh;

	UMaterialInstanceDynamic* DynamicMaterialInstance;
	UMaterialInterface* OriginalMaterial;

	bool ChestStateBool = false;

	float MinSpawnOffset = 85.0f;
	float MaxSpawnOffset = 115.0f;
	float ZSpawnOffset = 50.0f;

	void SpawnBall();
	float RandomFloat(float Min, float Max);
};
