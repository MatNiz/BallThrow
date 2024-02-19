// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Chest.h"
#include "Ball.h"
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

	for (AActor* Actor : BallArray)
	{
		ABall* Ball = Cast<ABall>(Actor);
		if (Ball != nullptr && BallInHandBool == false)
		{
			Ball->PickUp(this);
			BallInHandRef = Ball;
			BallInHandBool = true;
		}
	}

}


void AMyCharacter::ThrowBall()
{
	ABall* Ball = Cast<ABall>(BallInHandRef);
	if (Ball != nullptr)
	{
		Ball->Throw();
		BallInHandRef = nullptr;
		BallInHandBool = false;
	}
}


void AMyCharacter::PickUpBall(AActor* BallToPickUp)
{
	if (BallToPickUp)
	{
		// ZnajdŸ koœæ, do której chcesz przypi¹æ pi³kê
		FName SocketName = BallSocket; // Zast¹p "SocketName" nazw¹ koœci

		// Przypnij pi³kê do konkretnej koœci
		BallToPickUp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
	}
}