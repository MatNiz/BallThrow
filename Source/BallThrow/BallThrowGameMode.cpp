// Copyright Epic Games, Inc. All Rights Reserved.

#include "BallThrowGameMode.h"


ABallThrowGameMode::ABallThrowGameMode()
{


}

void ABallThrowGameMode::SetPlayerWidget(class UBallCounterWidget* NewPlayerWidget)
{
	PlayerWidget = NewPlayerWidget;
}

UBallCounterWidget* ABallThrowGameMode::GetPlayerWidget()
{
	return PlayerWidget;
}
