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

	UPROPERTY(EditAnywhere, Category = "Properties")
		TSubclassOf<class ABallCollectorCharacter> BallCollectorClass;

	//UPROPERTY(EditAnywhere, Category = "Properties")
	//	AChest& MyChestInstanceRef = *MyChestInstancePointer;

	TArray<AActor*> ChessArray;
	TArray<AActor*> ChestNearbyArray;
	TArray<AActor*> BallArray;

	AActor* BallInHandRef;

	bool BallThrown = false;
	bool BallInHand = false;


	float ChestInteractDistance = 150.0f;
	float BallInteractDistance = 150.0f;

	float ThrowSpeed = 1000.0f;
	float ThrowZOffset = 800.0f;

	void PickUpBall(AActor* BallToPickUp);
	void ThrowBall(AActor* BallToPickUp);

};
