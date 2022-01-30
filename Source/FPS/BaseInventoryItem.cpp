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
	
	
}

void ABaseInventoryItem::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseInventoryItem::Overlap);
}

void ABaseInventoryItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseInventoryItem::Use(AFPSCharacter* Character)
{
	
}

void ABaseInventoryItem::Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto Character = Cast<AFPSCharacter>(OtherActor);
	if (IsValid(Character))
	{
		Character->GetInventorySystem()->AddSlot(this, 1);
	}
}
