#pragma once

#include "CoreMinimal.h"
#include "BaseInventoryItem.h"
#include "HealInventoryItem.generated.h"

UCLASS()
class FPS_API AHealInventoryItem : public ABaseInventoryItem
{
	GENERATED_BODY()
public:
	virtual void Use(AFPSCharacter* Character) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float HealAmount;
	
	AHealInventoryItem();
protected:
	virtual void BeginPlay() override;
};
