// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BallCollectorController.generated.h"

/**
 *
 */
UCLASS()
class THIRDPERSONGAME_API ABallCollectorController : public AAIController
{
	GENERATED_BODY()

public:
	ABallCollectorController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());
	void BeginPlay() override;
	void OnPossess(APawn* const MyPawn) override;
	class UBlackboardComponent* GetBlackboard() const;
	float GetInteractionDistance();

private:
	class UBehaviorTreeComponent* BehaviorTreeComponent;
	class UBehaviorTree* BehaviorTree;
	class UBlackboardComponent* Blackboard;

	float InteractionDistance = 200.0f;
};
