// Copyright Epic Games, Inc. All Rights Reserved.

#include "BallThrowGameMode.h"


ABallThrowGameMode::ABallThrowGameMode()
{

}

void ABallThrowGameMode::BeginPlay()
{

    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PlayerController = It->Get();
        AddWidgetForPlayer(PlayerController);
    }

}

UBallCounterWidget* ABallThrowGameMode::GetWidgetForPlayer(AController* Controller)
{
    UBallCounterWidget** WidgetInstancePtr = PlayerWidgets.Find(Controller);
    if (WidgetInstancePtr)
    {
        return *WidgetInstancePtr;
    }
    return nullptr;
}

void ABallThrowGameMode::AddWidgetForPlayer(AController* Controller)
{
    if (Controller)
    {
        UBallCounterWidget* WidgetInstance = CreateWidget<UBallCounterWidget>(GetWorld(), WidgetClass);
        if (WidgetInstance)
        {
            WidgetInstance->AddToViewport();

            PlayerWidgets.Add(Controller, WidgetInstance);
        }
    }
}