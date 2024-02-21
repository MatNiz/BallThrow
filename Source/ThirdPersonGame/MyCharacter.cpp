// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Chest.h"
#include "Ball.h"
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>
#include <Subsystems/PanelExtensionSubsystem.h>
#include <Components/WidgetComponent.h>
#include "BallCollectorCharacter.h"
#include "BallCollectorController.h"
#include "GameFramework/HUD.h"
#include "BallCounterHUD.h"
#include "BallCounterWidget.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChest::StaticClass(), ChessArray);
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		AHUD* PlayerHUD = PlayerController->GetHUD();
		if (PlayerHUD)
		{
			ABallCounterHUD* MyHUD = Cast<ABallCounterHUD>(PlayerHUD);
			if (MyHUD)
			{
				UUserWidget* UserWidget = MyHUD->GetUIWidget();
				if (UserWidget)
				{
					BallCounterWidget = Cast<UBallCounterWidget>(UserWidget);
				}
			}
		}
	}

}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CharacterLocation = GetActorLocation();
	ChestNearbyArray.Empty();

	for (AActor* Actor : ChessArray)
	{
		/*FString VariableValueAsString = FString::Printf(TEXT("Wartoœæ zmiennej: %f"), DistanceToWantedActor);
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, VariableValueAsString);*/

		AChest* Chest = Cast<AChest>(Actor);
		if (Chest != nullptr)
		{
			FVector ActorLocation = Actor->GetActorLocation();
			float DistanceToWantedActor = (ActorLocation - CharacterLocation).Size();
			if (DistanceToWantedActor <= InteractionDistance)
			{
				Chest->CloseColorChange();
				ChestNearbyArray.Add(Actor);
			}
			else
			{
				Chest->FarColorChange();
			}
		}
	}

	TArray<AActor*> Array;
	BallArray.Empty();

	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABall::StaticClass(), Array);
	}

	for (AActor* Actor : Array)
	{
		/*FString VariableValueAsString = FString::Printf(TEXT("Wartoœæ zmiennej: %f"), DistanceToWantedActor);
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, VariableValueAsString);*/

		FVector ActorLocation = Actor->GetActorLocation();
		float DistanceToWantedActor = (ActorLocation - CharacterLocation).Size();
		if (DistanceToWantedActor <= InteractionDistance)
		{
			BallArray.Add(Actor);
		}
	}

}


void AMyCharacter::Interact()
{
	for (AActor* Actor : ChestNearbyArray)
	{
		AChest* Chest = Cast<AChest>(Actor);
		if (Chest != nullptr)
		{
			Chest->ChestInteracton();
		}
	}

	for (AActor* Actor : BallArray)
	{
		ABall* Ball = Cast<ABall>(Actor);
		//BallInHandRef = Cast<ABall>(Actor);
		if (Ball != nullptr && BallInHand == false)
		{
			Ball->PickUp(this);
			//BallInHandRef = Ball;
			ActorInHandRef = Ball;
			BallInHand = true;

			BallCounterWidget->ChangeBallCounterText(FText::FromString("Ball: 1"));

			SpawnNewBallCollector();
		}
	}
}

void AMyCharacter::ThrowBall()
{
	ABall* Ball = Cast<ABall>(ActorInHandRef);
	if (Ball != nullptr && BallInHand == true)
	{
		Ball->Throw(this, ThrowSpeed, ThrowZOffset);
		Ball->ToggleNiagara();
		BallInHand = false;

		BallCounterWidget->ChangeBallCounterText(FText::FromString("Ball: 0"));
	}
}

void AMyCharacter::SpawnNewBallCollector()
{
	ABallCollectorCharacter* NewCharacter = GetWorld()->SpawnActor<ABallCollectorCharacter>(BallCollectorClass, FTransform (FRotator(0, 0, 0), BallCollectorSpawnLocation, FVector(1, 1, 1)));
	ABallCollectorController* NewController = GetWorld()->SpawnActor<ABallCollectorController>(BallCollectorControllerClass);

	if (NewController && NewCharacter)
	{
		NewController->Possess(NewCharacter);
	}
}




AActor* AMyCharacter::GetBallInHandRef() const
{
	return ActorInHandRef;
}

void AMyCharacter::ClearBallInHandRef()
{
	ActorInHandRef = nullptr;
}

bool AMyCharacter::GetBallInHand()
{
	return BallInHand;
}






void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AMyCharacter::Interact);
	PlayerInputComponent->BindAction("ThrowBall", IE_Pressed, this, &AMyCharacter::ThrowBall);

}


void AMyCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}


void AMyCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}