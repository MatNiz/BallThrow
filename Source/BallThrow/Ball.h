// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"


UCLASS()
class BALLTHROW_API ABall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void Throw(AActor* Actor, float ThrowSpeed, float ThrowZOffset);
	void PickUp(AActor* Actor);
	void ToggleNiagara();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	class UStaticMeshComponent* BallMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	class UNiagaraComponent* BallNiagaraComponent;


	bool IsPickedUp = false;
	bool IsInTheAir = false;
	bool IsNiagaraOn = false;


	UFUNCTION()
	void OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
