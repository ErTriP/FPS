#include "InventorySystem.h"

#include "FPSCharacter.h"
#include "Net/UnrealNetwork.h"

UInventorySystem::UInventorySystem()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
	
	DropDistance = 300.f;
}


void UInventorySystem::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UInventorySystem::Overlap);
}

void UInventorySystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UInventorySystem, InventoryItems, COND_AutonomousOnly)
}

void UInventorySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventorySystem::OnRep_InventoryItems()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Black, "RepInventory");
}

void UInventorySystem::AddSlotServer_Implementation(ABaseInventoryItem* item, int32 count)
{
	item->SetActorHiddenInGame(true);
	item->SetActorEnableCollision(false);
	item->SetActorLocationAndRotation(FVector(0,0,0), GetOwner()->GetActorRotation());
	SetActorLocAndRotMulticast(item, FVector(0,0,0), GetOwner()->GetActorRotation());
	InventoryItems.Add(item);
}

void UInventorySystem::UseItem(ABaseInventoryItem* item)
{
	if (InventoryItems.Contains(item))
	{
		item->Use(Cast<AFPSCharacter>(GetOwner()));
		InventoryItems.Remove(item);
		item->Destroy();
		
	}
	
}

void UInventorySystem::DropItemServer_Implementation(ABaseInventoryItem* item)
{
	auto Character = GetOwner();
	FVector LocationToDrop(Character->GetActorLocation() + Character->GetActorForwardVector() * DropDistance);
	item->SetActorHiddenInGame(false);
	item->SetActorLocationAndRotation(LocationToDrop, GetOwner()->GetActorRotation());
	item->SetActorEnableCollision(true);
	SetActorLocAndRotMulticast(item, LocationToDrop, GetOwner()->GetActorRotation());
	InventoryItems.Remove(item);
}

void UInventorySystem::SetActorLocAndRotMulticast_Implementation(ABaseInventoryItem* item, FVector Loc, FRotator Rot)
{
	item->SetActorLocationAndRotation(Loc, Rot);
}

void UInventorySystem::Overlap(AActor* OverlappedActor, AActor* OtherActor )
{
	auto Item = Cast<ABaseInventoryItem>(OtherActor);
	if(IsValid(Item))
	{
		AddSlotServer(Item, 1);
	}
}

