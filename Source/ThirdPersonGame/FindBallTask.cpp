// Fill out your copyright notice in the Description page of Project Settings.


#include "FindBallTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "BallCollectorController.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BlackboardKeys.h"

UFindBallTask::UFindBallTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Ball");
}

EBTNodeResult::Type UFindBallTask::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	auto const Controller = Cast<ABallCollectorController>(owner_comp.GetAIOwner());
	auto const BallCollector = Controller->GetPawn();

	FVector const Origin = BallCollector->GetActorLocation();
	FNavLocation ResultLocation;

	UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());

	if (nav_sys->GetRandomPointInNavigableRadius(Origin, SearchRadius, ResultLocation, nullptr))
	{

		Controller->GetBlackboard()->SetValueAsVector(GetSelectedBlackboardKey(), ResultLocation.Location);
	}

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Type();
}
