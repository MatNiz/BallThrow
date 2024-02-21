// Fill out your copyright notice in the Description page of Project Settings.


#include "BallCounterWidget.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

void UBallCounterWidget::NativeConstruct()
{

}

void UBallCounterWidget::ChangeBallCounterText(FText text)
{
	if (BallCounterText)
	{
		BallCounterText->SetText(text);
	}
}

