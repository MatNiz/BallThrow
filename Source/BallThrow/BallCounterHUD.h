// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BallCounterHUD.generated.h"

/**
 * 
 */
UCLASS()
class BALLTHROW_API ABallCounterHUD : public AHUD
{
	GENERATED_BODY()

public:
	ABallCounterHUD();
	void BeginPlay() override;


private:
	TSubclassOf<class UUserWidget> UIBPClass;
	UUserWidget* UIWidget;
	
};
