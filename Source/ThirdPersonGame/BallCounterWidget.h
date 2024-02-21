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

	UFUNCTION()
		void ChangeBallCounterText(FText text);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* BallCounterText;

};
