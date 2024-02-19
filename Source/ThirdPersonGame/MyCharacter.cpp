// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Chest.h"
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>


AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChest::StaticClass(), ActorsArray);
	}

}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CharacterLocation = GetActorLocation();
	ChestNearbyArray.Empty();


	for (AActor* Actor : ActorsArray)
	{
		/*FString VariableValueAsString = FString::Printf(TEXT("Warto�� zmiennej: %f"), DistanceToWantedActor);
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, VariableValueAsString);*/

		AChest* Chest = Cast<AChest>(Actor);
		if (Chest != nullptr)
		{
			FVector ActorLocation = Actor->GetActorLocation();
			float DistanceToWantedActor = (ActorLocation - CharacterLocation).Size();
			if (DistanceToWantedActor <= ChestInteractRadius)
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


void AMyCharacter::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "E Pressed");

	for (AActor* Actor : ChestNearbyArray)
	{
		AChest* Chest = Cast<AChest>(Actor);
		if (Chest != nullptr)
		{
			Chest->ChestInteracton();
		}
	}
}


void AMyCharacter::ThrowBall()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, "Ball Thrown");
}