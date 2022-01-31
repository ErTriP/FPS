#include "BaseInventoryItem.h"

#include "FPSCharacter.h"

ABaseInventoryItem::ABaseInventoryItem()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxComponent);
	//BoxComponent->SetSimulatePhysics(true);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	bReplicates = true;
}

void ABaseInventoryItem::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseInventoryItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseInventoryItem::Use(AFPSCharacter* Character)
{
	
}
