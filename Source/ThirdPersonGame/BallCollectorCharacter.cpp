// Fill out your copyright notice in the Description page of Project Settings.


#include "BallCollectorCharacter.h"

// Sets default values
ABallCollectorCharacter::ABallCollectorCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABallCollectorCharacter::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ABallCollectorCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABallCollectorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

