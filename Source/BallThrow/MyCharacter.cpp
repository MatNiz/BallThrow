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
#include "BallThrowGameMode.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;


	InteractionSphere = CreateDefaultSubobject<USphereComponent>("InteractionSphere");
	InteractionSphere->SetSphereRadius(InteractionRadius);
	InteractionSphere->SetupAttachment(RootComponent);

	IsBallInHand = false;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();


	ABallThrowGameMode* GameMode = Cast<ABallThrowGameMode>(GetWorld()->GetAuthGameMode());
	BallCounterWidget = GameMode->GetPlayerWidget();
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (OverlapingActors.Num() == 0)
	{
		NearestActor = nullptr;
	}
	else
	{
		FVector CharacterLocation = GetActorLocation();

		float NearestDistance = MAX_FLT;
		NearestActor = nullptr;

		for (AActor* Actor : OverlapingActors)
		{
			float DistanceToPlayer = FVector::Distance(Actor->GetActorLocation(), CharacterLocation);
			if (DistanceToPlayer < NearestDistance)
			{
				NearestDistance = DistanceToPlayer;
				NearestActor = Actor;
			}
		}
	}
	NearestActorHandling();
}


void AMyCharacter::NearestActorHandling()
{
	if (NearestActor && IsBallInHand == false)
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
	if (NearestActor)
	{
		if (AChest* Chest = Cast<AChest>(NearestActor))
		{
			Chest->ChestInteracton();
		}

		ABall* Ball = Cast<ABall>(NearestActor);
		if (Ball && IsBallInHand == false)
		{
			Ball->PickUp(this);
			//BallInHandRef = Ball;
			ActorInHandRef = Ball;
			IsBallInHand = true;

			BallCounterWidget->ChangeBallCounterText(FText::FromString("Ball: 1"));
			SpawnNewBallCollector();
		}
	}
}

void AMyCharacter::ThrowBall()
{
	ABall* Ball = Cast<ABall>(ActorInHandRef);
	if (Ball != nullptr && IsBallInHand == true)
	{
		Ball->Throw(this, ThrowSpeed, ThrowZOffset);
		Ball->ToggleNiagara();
		IsBallInHand = false;

		BallCounterWidget->ChangeBallCounterText(FText::FromString("Ball: 0"));
	}
}

void AMyCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AChest* Chest = Cast<AChest>(OtherActor);
	ABall* Ball = Cast<ABall>(OtherActor);

	if (Chest || Ball)
	{
		OverlapingActors.Add(OtherActor);
	}
}

void AMyCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	OverlapingActors.Remove(OtherActor);
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
	return IsBallInHand;
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