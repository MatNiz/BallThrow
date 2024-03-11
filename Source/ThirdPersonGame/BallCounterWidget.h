// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BallCounterWidget.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONGAME_API UBallCounterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;


	void ChangeBallCounterText(FText text);
	void ChangeInteractionText(FText text);
	void HideInteractionText();

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* BallCounterText;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* InteractionText;

};
