// Fill out your copyright notice in the Description page of Project Settings.


#include "GoToBallTask.h"
#include "BallCollectorController.h"
#include "BlackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Ball.h"

UGoToBallTask::UGoToBallTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Go To Ball");
}

EBTNodeResult::Type UGoToBallTask::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	auto const Controller = Cast<ABallCollectorController>(owner_comp.GetAIOwner());

	UObject* Object = Controller->GetBlackboard()->GetValueAsObject(BlackboardKeysNamespace::ball_ref);
	auto const BallRef = Cast<AActor>(Object);
	auto const BallCollectorPawn = Controller->GetPawn();

	if (BallRef)
	{
		//UE_LOG(LogTemp, Warning, TEXT("BallRef true"));
		auto BallLocation = BallRef->GetActorLocation();

		Controller->GetBlackboard()->SetValueAsVector(BlackboardKeysNamespace::target_location, BallLocation);

		float DistanceToActor = (BallCollectorPawn->GetActorLocation() - BallLocation).Size();

		if (DistanceToActor <= Controller->GetInteractionDistance())
		{
			//UE_LOG(LogTemp, Warning, TEXT("distacne good"));
			ABall* Ball = Cast<ABall>(BallRef);
			if (Ball != nullptr)
			{
				//UE_LOG(LogTemp, Warning, TEXT("casted good"));
				Ball->PickUp(BallCollectorPawn);
//				Ball->ToggleNiagara();
				Controller->GetBlackboard()->SetValueAsBool(BlackboardKeysNamespace::move_to_player, true);
			}
		}
	}


	return EBTNodeResult::Type();
}
