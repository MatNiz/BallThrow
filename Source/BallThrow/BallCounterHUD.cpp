// Fill out your copyright notice in the Description page of Project Settings.


#include "BallCounterHUD.h"
#include "BallCounterWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

ABallCounterHUD::ABallCounterHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ui(TEXT("/Game/MyContent/Blueprints/UI/BP_BallCounterWidget"));
	if (ui.Succeeded())
	{
		UIBPClass = ui.Class;
	}
}

void ABallCounterHUD::BeginPlay()
{
	Super::BeginPlay();

	if (UIBPClass)
	{
		UIWidget = CreateWidget<UUserWidget>(GetWorld(), UIBPClass);
		if (UIWidget)
		{
			UIWidget->AddToViewport();
		}
	}

}
