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


	void SetPlayerWidget(class UBallCounterWidget* NewPlayerWidget);
	class UBallCounterWidget* GetPlayerWidget();


private:
	class UBallCounterWidget* PlayerWidget;
	

};
