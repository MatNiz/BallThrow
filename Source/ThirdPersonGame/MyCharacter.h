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

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Interact();
	void ThrowBall();

	//UPROPERTY(EditAnywhere, Category = "Properties")
	//	AChest& MyChestInstanceRef = *MyChestInstancePointer;

	TArray<AActor*> ActorsArray;
	TArray<AActor*> ChestNearbyArray;

	float ChestInteractRadius = 200.0f;

};
