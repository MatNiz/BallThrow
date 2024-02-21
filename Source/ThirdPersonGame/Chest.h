// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chest.generated.h"

UCLASS()
class THIRDPERSONGAME_API AChest : public AActor
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
	void CloseColorChange();
	void FarColorChange();


private:
	UPROPERTY(EditAnywhere, Category = "Properties")
		TSubclassOf<class ABall> BallClass;

	class UStaticMeshComponent* ChestMesh;
	class UStaticMesh* ChestClosedMesh;
	class UStaticMesh* ChestOpenMesh;

	UMaterialInstanceDynamic* DynamicMaterialInstance;
	UMaterialInterface* OriginalMaterial;

	bool Open = false;

	float MinSpawnOffset = 85.0f;
	float MaxSpawnOffset = 115.0f;
	float ZSpawnOffset = 50.0f;


	void SpawnBall();
	float RandomFloat(float Min, float Max);

};
