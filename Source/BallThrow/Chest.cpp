#include "Chest.h"
#include "Ball.h"
#include <random>

// Sets default values
AChest::AChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ChestStateBool = false;

	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>("ChestMesh");
	RootComponent = ChestMesh;

}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();


	ChestMesh->SetStaticMesh(ChestClosedMesh);

	OriginalMaterial = ChestMesh->GetMaterial(0);
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
	if (ChestStateBool == false)
	{
		SpawnBall();
		ChestMesh->SetStaticMesh(ChestOpenMesh);
	}
	else
	{
		ChestMesh->SetStaticMesh(ChestClosedMesh);
	}
	ChestStateBool = !ChestStateBool;
}

bool AChest::GetChestStateBool()
{
	return ChestStateBool;
}


void AChest::SpawnBall()
{
	FTransform SpawnTransform = GetActorTransform();

	SpawnTransform.SetLocation(GetActorLocation() + GetActorForwardVector() * RandomFloat(MinSpawnOffset, MaxSpawnOffset) + FVector(0, 0, ZSpawnOffset));
	GetWorld()->SpawnActor<ABall>(BallClass, SpawnTransform);
}

float AChest::RandomFloat(float Min, float Max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(Min, Max);

	return dis(gen);
}
