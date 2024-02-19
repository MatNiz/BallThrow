#include "Chest.h"
#include "Ball.h"

// Sets default values
AChest::AChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>("ChestMesh");

}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();

	OriginalMaterial = ChestMesh->GetMaterial(0);

	// Utwórz instancjê dynamicznego materia³u
	DynamicMaterialInstance = UMaterialInstanceDynamic::Create(OriginalMaterial, this);
	ChestMesh->SetMaterial(0, DynamicMaterialInstance);

}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChest::ChestInteracton()
{
	if (Open == false)
	{
		SpawnBall();
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "CloseChest");

	Open = !Open;

}

void AChest::CloseColorChange()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, "Chest Close");
	DynamicMaterialInstance->SetVectorParameterValue("Color", FLinearColor::Green);
}

void AChest::FarColorChange()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, "Chest Far");
	DynamicMaterialInstance->SetVectorParameterValue("Color", FLinearColor::White);
}




void AChest::SpawnBall()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Ball Spawned");

	FTransform SpawnTransform = GetActorTransform();

	SpawnTransform.SetLocation(GetActorLocation() + GetActorForwardVector() * SpawnOffset);
	GetWorld()->SpawnActor<ABall>(BallClass, SpawnTransform);

}
