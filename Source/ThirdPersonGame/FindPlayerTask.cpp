// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BallCollectorController.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "BlackboardKeys.h"
#include "Ball.h"

UFindPlayerTask::UFindPlayerTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Player");
}

EBTNodeResult::Type UFindPlayerTask::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	auto const Controller = Cast<ABallCollectorController>(owner_comp.GetAIOwner());

	ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector const PlayerLocation = Player->GetActorLocation();

	auto const BallCollectorPawn = Controller->GetPawn();

	UObject* Object = Controller->GetBlackboard()->GetValueAsObject(BlackboardKeysNamespace::ball_ref);
	auto const BallRef = Cast<AActor>(Object);


	float DistanceToActor = (BallCollectorPawn->GetActorLocation() - PlayerLocation).Size();

	if (DistanceToActor <= Controller->GetInteractionDistance())
	{
		ABall* Ball = Cast<ABall>(BallRef);
		if (Ball != nullptr)
		{
			Ball->Throw(BallCollectorPawn, 100, 1);
			BallCollectorPawn->Destroy();
		}
	}

	Controller->GetBlackboard()->SetValueAsVector(BlackboardKeysNamespace::target_location, PlayerLocation + Player->GetActorForwardVector() * OffsetDistance);

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Type();
}
