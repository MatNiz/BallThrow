// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BallCounterWidget.h"
#include "BallThrowGameMode.generated.h"

UCLASS(minimalapi)
class ABallThrowGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABallThrowGameMode();

	void BeginPlay();


	UBallCounterWidget* GetWidgetForPlayer(AController* Controller);
	void AddWidgetForPlayer(AController* Controller);

private:
	UPROPERTY(EditDefaultsOnly, Category = "References")
		TSubclassOf<class UBallCounterWidget> WidgetClass;

	TMap<AController*, class UBallCounterWidget*> PlayerWidgets;

};
