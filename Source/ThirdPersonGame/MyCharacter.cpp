// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Chest.h"
#include "Ball.h"
#include "BallCounterWidget.h"
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>
#include <Subsystems/PanelExtensionSubsystem.h>
#include <Components/WidgetComponent.h>


AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//BallCounterWidget = FPanelExtensionFactory::CreateWidget<UUserWidget>(GetWorld(), BP_BallCounterWidget);


	//static ConstructorHelpers::FObjectFinder<UUserWidget> obj(TEXT("WidgetBlueprint'/Game/MyContent/Blueprints/BP_BallCounterWidget.BP_BallCounterWidget'"));

	//// Wczytanie klasy widgetu
	//TSubclassOf<UUserWidget> WidgetClass = BallCounterWidget;

	//TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/MyContent/Blueprints/BP_BallCounterWidget.BP_BallCounterWidget_C'"));

	//TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUserWidget>(nullptr, "/Game/MyContent/Blueprints/BP_BallCounterWidget.BP_BallCounterWidget_C");

	//TSubclassOf<UUserWidget> WidgetClass = BP_BallCounterWidget_C;


	//// Utworzenie instancji widgetu
	//UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(this, BallCounterWidget);

	//// Dodanie widgetu do widoku
	//BallCounterWidget->AddToViewport();

	// SprawdŸ, czy widget zosta³ poprawnie utworzony
	//if (BallCounterWidget)
	//{
	//	// Dodaj widget do widoku gracza
	//	BallCounterWidget->AddToViewport();
	//}


	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChest::StaticClass(), ChessArray);
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
			if (DistanceToWantedActor <= ChestInteractDistance)
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
		if (DistanceToWantedActor <= BallInteractDistance)
		{
			BallArray.Add(Actor);
		}
	}

}


void AMyCharacter::Interact()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "E Pressed");

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
		if (Ball != nullptr && BallInHandBool == false)
		{
			Ball->DisablePhysicAndCollision(this);
			BallInHandRef = Ball;
			BallInHandBool = true;
			PickUpBall(Ball);
		}
	}

}


void AMyCharacter::ThrowBall()
{
	ABall* Ball = Cast<ABall>(BallInHandRef);
	if (Ball != nullptr)
	{
		Ball->Throw(this);
		BallInHandRef = nullptr;
		BallInHandBool = false;
	}
}


void AMyCharacter::PickUpBall(AActor* BallToPickUp)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "PickUpBall");

	BallToPickUp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "BallSocket");
}

AActor* AMyCharacter::GetBallInHandRef() const
{
	return BallInHandRef;
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