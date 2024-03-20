// Fill out your copyright notice in the Description page of Project Settings.


#include "BallCounterWidget.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "BallThrowGameMode.h"

void UBallCounterWidget::NativeConstruct()
{
	ABallThrowGameMode* GameMode = Cast<ABallThrowGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->SetPlayerWidget(this);
}

void UBallCounterWidget::ChangeBallCounterText(FText text)
{
	if (BallCounterText)
	{
		BallCounterText->SetText(text);
	}
}

void UBallCounterWidget::ChangeInteractionText(FText text)
{
	if (InteractionText)
	{
		InteractionText->SetVisibility(ESlateVisibility::Visible);
		InteractionText->SetText(text);
	}
}

void UBallCounterWidget::HideInteractionText()
{
	if (InteractionText)
	{
		InteractionText->SetVisibility(ESlateVisibility::Hidden);
	}
}

