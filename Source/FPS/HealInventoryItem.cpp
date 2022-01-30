#include "HealInventoryItem.h"
#include "FPSCharacter.h"

AHealInventoryItem::AHealInventoryItem()
{
	HealAmount = 0.0f;
}

void AHealInventoryItem::BeginPlay()
{
	Super::BeginPlay();
}

void AHealInventoryItem::Use(AFPSCharacter* Character)
{
	Super::Use(Character);

	Character->AddHealth(HealAmount);
	
}
