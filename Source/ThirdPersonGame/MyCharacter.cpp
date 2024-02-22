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


	TArray<AActor*> FoundActors;
	TArray<AActor*> AllChests;
	TArray<AActor*> AllBalls;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChest::StaticClass(), AllChests);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABall::StaticClass(), AllBalls);

	FoundActors.Append(AllChests);
	FoundActors.Append(AllBalls);

	FVector CharacterLocation = GetActorLocation();

	float NearestDistance = MAX_FLT;
	NearestActor = nullptr;

	for (AActor* Actor : FoundActors)
	{
		float DistanceToPlayer = FVector::Distance(Actor->GetActorLocation(), CharacterLocation);

		if (DistanceToPlayer < NearestDistance)
		{
			NearestDistance = DistanceToPlayer;
			NearestActor = Actor;
		}
	}

	if (NearestDistance >= InteractionDistance)
	{
		NearestActor = nullptr;
	}

	NearestActorHandling();
}


void AMyCharacter::NearestActorHandling()
{
	if (NearestActor)
	{
		if (AChest* Chest = Cast<AChest>(NearestActor))
		{
			if (Chest->GetChestStateBool())
				BallCounterWidget->ChangeInteractionText(FText::FromString("E: Close Chest"));
			else
				BallCounterWidget->ChangeInteractionText(FText::FromString("E: Open Chest"));
		}

		if (ABall* Ball = Cast<ABall>(NearestActor))
		{
			BallCounterWidget->ChangeInteractionText(FText::FromString("E: Pick Up Ball"));
		}
	}
	else
	{
		BallCounterWidget->HideInteractionText();
	}
}


void AMyCharacter::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interaction"));//////////////////////////////////////////////////////////////////
	if (NearestActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Interaction"));

		if (AChest* Chest = Cast<AChest>(NearestActor))
		{
			Chest->ChestInteracton();
		}

		ABall* Ball = Cast<ABall>(NearestActor);
		if (Ball && BallInHandBool == false)
		{
			Ball->PickUp(this);
			//BallInHandRef = Ball;
			ActorInHandRef = Ball;
			BallInHandBool = true;

			BallCounterWidget->ChangeBallCounterText(FText::FromString("Ball: 1"));
			SpawnNewBallCollector();
		}
	}
}

void AMyCharacter::ThrowBall()
{
	ABall* Ball = Cast<ABall>(ActorInHandRef);
	if (Ball != nullptr && BallInHandBool == true)
	{
		Ball->Throw(this, ThrowSpeed, ThrowZOffset);
		Ball->ToggleNiagara();
		BallInHandBool = false;

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


AActor* AMyCharacter::GetActorInHandRef() const
{
	return ActorInHandRef;
}

void AMyCharacter::ClearBallInHandRef()
{
	ActorInHandRef = nullptr;
}

bool AMyCharacter::GetBallInHandBool()
{
	return BallInHandBool;
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