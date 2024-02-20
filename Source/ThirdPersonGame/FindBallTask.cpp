// Fill out your copyright notice in the Description page of Project Settings.


#include "FindBallTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "BallCollectorController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
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
	auto const BallCollector = Controller->GetPawn();

	FVector const Origin = BallCollector->GetActorLocation();
	FNavLocation ResultLocation;

	UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());

	/*if (nav_sys->GetRandomPointInNavigableRadius(Origin, SearchRadius, ResultLocation, nullptr))
	{

		Controller->GetBlackboard()->SetValueAsVector(BlackboardKeysNamespace::target_location, ResultLocation.Location);
	}*/


	ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//ABall* MyCharacterInstance = Cast<ABall>(Player);

	//auto const MyCharacterInstance = Cast<AMyCharacter>(Player);

	if (auto const MyCharacterInstance = Cast<AMyCharacter>(Player))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Cast na myCharacter"); 

		if (SearchedBall)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "przekazanie ref pi³ki");
			FVector NewLocation = SearchedBall->GetActorLocation();
			Controller->GetBlackboard()->SetValueAsVector(BlackboardKeysNamespace::target_location, NewLocation);
			//Controller->GetBlackboard()->SetValueAsBool(BlackboardKeysNamespace::start_movement, true);
		}
		else
		{
			SearchedBall = MyCharacterInstance->GetBallInHandRef();
		}

	}

	/*FVector const PlayerLocation = Player->GetActorLocation();

	Controller->GetBlackboard()->SetValueAsVector(BlackboardKeysNamespace::target_location, PlayerLocation);*/

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Type();
}
