#pragma once

#include "CoreMinimal.h"
#include "BaseInventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventorySystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UInventorySystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventorySystem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<ABaseInventoryItem*, int32> InventoryItems;

	UPROPERTY(EditDefaultsOnly)
	float DropDistance;

	UFUNCTION(BlueprintCallable)
	void AddSlot(ABaseInventoryItem* item, int32 count);

	UFUNCTION(BlueprintCallable)
	void UseItem(ABaseInventoryItem* item);

	UFUNCTION(BlueprintCallable)
	void DropItem(ABaseInventoryItem* item);
	
};
