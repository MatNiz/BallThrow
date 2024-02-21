// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GoToBallTask.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class THIRDPERSONGAME_API UGoToBallTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UGoToBallTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory);

};
