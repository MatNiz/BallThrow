// Fill out your copyright notice in the Description page of Project Settings.


#include "FindBallTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BallCollectorController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "BlackboardKeys.h"
#include "MyCharacter.h"

UFindBallTask::UFindBallTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Ball");
}

EBTNodeResult::Type UFindBallTask::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	auto const Controller = Cast<ABallCollectorController>(owner_comp.GetAIOwner());

	ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const MyCharacter = Cast<AMyCharacter>(Player);
	auto SearchedBall = MyCharacter->GetBallInHandRef();

	if (MyCharacter->GetBallThrown() && SearchedBall)
	{
		UE_LOG(LogTemp, Warning, TEXT("ball throw true && searched ball przekazana"));

		Controller->GetBlackboard()->SetValueAsBool(BlackboardKeysNamespace::move_to_ball, true);
		Controller->GetBlackboard()->SetValueAsObject(BlackboardKeysNamespace::ball_ref, SearchedBall);

		MyCharacter->ClearBallInHandRef();
	}

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Type();
}
