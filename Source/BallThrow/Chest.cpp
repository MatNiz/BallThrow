#include "Chest.h"
#include "Ball.h"


// Sets default values
AChest::AChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	IsChestOpen = false;

	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>("ChestMesh");
	RootComponent = ChestMesh;

	SpawnLocationComponent = CreateDefaultSubobject<USceneComponent>("SpawnLocationComponent");
	SpawnLocationComponent->AttachTo(RootComponent);
	SpawnLocationComponent->SetRelativeLocation(SpawnOffset);
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
	if (IsChestOpen == false)
	{
		SpawnBall();
		ChestMesh->SetStaticMesh(ChestOpenMesh);
	}
	else
	{
		ChestMesh->SetStaticMesh(ChestClosedMesh);
	}
	IsChestOpen = !IsChestOpen;
}

bool AChest::GetIsChestOpen()
{
	return IsChestOpen;
}


void AChest::SpawnBall()
{
	GetWorld()->SpawnActor<ABall>(BallClass, SpawnLocationComponent->GetComponentTransform());
}

