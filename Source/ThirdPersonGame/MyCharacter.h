// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"


UCLASS()
class THIRDPERSONGAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//UPROPERTY(EditAnywhere)
	//UUserWidget* BallCounterWidget;

	class AActor* GetBallInHandRef() const;
	void ClearBallInHandRef();
	bool GetBallThrown();

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Interact();
	void ThrowBall();
	void SpawnNewBallCollector();


	//class ABall* BallInHandRef;
	AActor* ActorInHandRef;

	UPROPERTY(EditAnywhere, Category = "Properties")
		TSubclassOf<class ABallCollectorCharacter> BallCollectorClass;

	UPROPERTY(EditAnywhere, Category = "Properties")
		TSubclassOf<class ABallCollectorController> BallCollectorControllerClass;

	TArray<AActor*> ChessArray;
	TArray<AActor*> ChestNearbyArray;
	TArray<AActor*> BallArray;

	FVector BallCollectorSpawnLocation = FVector(0, 0, 180);

	bool BallThrown = false;
	bool BallInHand = false;

	float InteractionDistance = 150.0f;

	float ThrowSpeed = 1000.0f;
	float ThrowZOffset = 800.0f;


	//UPROPERTY(EditAnywhere, Category = "Properties")
//	AChest& MyChestInstanceRef = *MyChestInstancePointer;



};
