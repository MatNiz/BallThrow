// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonGameGameMode.h"
#include "UObject/ConstructorHelpers.h"

AThirdPersonGameGameMode::AThirdPersonGameGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/MyContent/Blueprints/BP_MyCharacter.BP_MyCharacter'"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}
