// Fill out your copyright notice in the Description page of Project Settings.


#include "BallCollectorController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "MyCharacter.h"


ABallCollectorController::ABallCollectorController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/MyContent/Blueprints/BallCollector/BT_BallCollector.BT_BallCollector'"));
	if (obj.Succeeded())
	{
		BehaviorTree = obj.Object;
	}
	BehaviorTreeComponent = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	Blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void ABallCollectorController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComponent->StartTree(*BehaviorTree);

}

void ABallCollectorController::OnPossess(APawn* const MyPawn)
{
	Super::OnPossess(MyPawn);
	if (Blackboard)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}

}

UBlackboardComponent* ABallCollectorController::GetBlackboard() const
{
	return Blackboard;
}
