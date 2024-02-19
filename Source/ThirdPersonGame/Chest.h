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


	UPROPERTY(EditAnywhere, Category = "Properties")
		class UStaticMeshComponent* ChestMesh;

	void ChestInteracton();
	void CloseColorChange();
	void FarColorChange();

	UMaterialInstanceDynamic* DynamicMaterialInstance;
	UMaterialInterface* OriginalMaterial;

private:
	UPROPERTY(EditAnywhere, Category = "Properties")
		TSubclassOf<class ABall> BallClass;

	bool Open = false;
	float SpawnOffset = 100.0f;

	void SpawnBall();


};
