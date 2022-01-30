#include "InventorySystem.h"

#include "FPSCharacter.h"

UInventorySystem::UInventorySystem()
{
	PrimaryComponentTick.bCanEverTick = true;

	DropDistance = 100.f;
}


void UInventorySystem::BeginPlay()
{
	Super::BeginPlay();
}

void UInventorySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventorySystem::AddSlot(ABaseInventoryItem* item, int32 count)
{
	item->TeleportTo(FVector(0,0,0), FRotator(0,0,0));
	item->GetBoxCollision()->Deactivate();
	if(InventoryItems.Contains(item))
	{
		InventoryItems[item] += count;
	}else
	{
		InventoryItems.Add(item, count);
	}
}


void UInventorySystem::UseItem(ABaseInventoryItem* item)
{
	if (InventoryItems.Contains(item))
	{
		item->Use(Cast<AFPSCharacter>(GetOwner()));
		InventoryItems[item] -= 1;
		if (InventoryItems[item] <= 0)
		{
			InventoryItems.Remove(item);
			item->Destroy();
		}
		
	}
	
}

void UInventorySystem::DropItem(ABaseInventoryItem* item)
{
	auto Character = GetOwner();
	FVector LocationToDrop(Character->GetActorLocation() + Character->GetActorForwardVector() * DropDistance);
	item->GetBoxCollision()->Activate();
	item->TeleportTo(LocationToDrop, Character->GetActorRotation());
	InventoryItems.Remove(item);
}

