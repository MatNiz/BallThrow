// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BallCollectorController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "BlackboardKeys.h"

UFindPlayerTask::UFindPlayerTask(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Player");
}

EBTNodeResult::Type UFindPlayerTask::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const Controller = Cast<ABallCollectorController>(owner_comp.GetAIOwner());

	FVector const PlayerLocation = Player->GetActorLocation();

	Controller->GetBlackboard()->SetValueAsVector(BlackboardKeysNamespace::target_location, PlayerLocation);


	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);


	return EBTNodeResult::Type();
}
