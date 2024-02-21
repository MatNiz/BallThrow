// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraComponent.h"
#include "MyCharacter.h"

// Sets default values
ABall::ABall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>("BallMesh");
	RootComponent = BallMesh;

	BallNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraFX"));
	BallNiagaraComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("NiagaraSystem'/Game/MyContent/NS_BallEffect.NS_BallEffect'"));
	if (NiagaraAsset.Succeeded())
	{
		BallNiagaraComponent->SetAsset(NiagaraAsset.Object);
	}

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	BallNiagaraComponent->Deactivate();

	BallMesh->OnComponentHit.AddDynamic(this, &ABall::OnBallHit);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsInTheAir)
	{
		FVector Velocity = BallMesh->GetPhysicsLinearVelocity();
		FRotator NewRotation = Velocity.Rotation();
		BallMesh->SetWorldRotation(NewRotation);
	}
}

void ABall::ToggleNiagara()
{
	UE_LOG(LogTemp, Warning, TEXT("ToggleNiagara"));
	if(IsNiagaraOn)
		BallNiagaraComponent->Deactivate();
	else
		BallNiagaraComponent->Activate();

	IsNiagaraOn = !IsNiagaraOn;
}

 
void ABall::OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (FirstHit)
	{
		FirstHit = false;
	}
	else
	{
		if (IsInTheAir)
		{
			IsInTheAir = false;
			ToggleNiagara();
		}
	}
}


void ABall::PickUp(AActor* Actor)
{
	if (IsPickedUp == false)
	{
		BallMesh->SetSimulatePhysics(false);
		BallMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		auto const ActorMesh = Actor->FindComponentByClass<USkeletalMeshComponent>();

		this->AttachToComponent(ActorMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "BallSocket");

		IsPickedUp = true;
	}
}

void ABall::Throw(AActor* Actor, float ThrowSpeed, float ThrowZOffset)
{
	if (IsPickedUp == true)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		BallMesh->SetSimulatePhysics(true);
		BallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BallMesh->SetCollisionProfileName("BlockAll");
		BallMesh->SetGenerateOverlapEvents(true);
		BallMesh->SetNotifyRigidBodyCollision(true);

		FVector ThrowVelocity = Actor->GetActorForwardVector() * ThrowSpeed + FVector(0.0f, 0.0f, ThrowZOffset);
		BallMesh->SetPhysicsLinearVelocity(ThrowVelocity, false);


		IsPickedUp = false;

		if (AMyCharacter* MyCharacter = Cast<AMyCharacter>(Actor))
		{
			IsInTheAir = true;
			FirstHit = true;
		}
	}
}
