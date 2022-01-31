#pragma once

#include "CoreMinimal.h"
#include "BaseInventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventorySystem.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItemsData
{
	GENERATED_BODY()
	UPROPERTY()
	ABaseInventoryItem* Item;

	UPROPERTY()
	int32 Count;

	FInventoryItemsData()
	{
		Item = nullptr;
		Count = 0;
	}
	
	FInventoryItemsData(ABaseInventoryItem*, int32)
	{
		Item = nullptr;
		Count = 0;
	}
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UInventorySystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventorySystem();

protected:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_InventoryItems)
	TArray<ABaseInventoryItem*> InventoryItems;

	UFUNCTION()
	void OnRep_InventoryItems();

	UPROPERTY(EditDefaultsOnly)
	float DropDistance;

	UFUNCTION(BlueprintCallable, Server, Unreliable)
	void AddSlotServer(ABaseInventoryItem* item, int32 count);

	UFUNCTION(BlueprintCallable)
	void UseItem(ABaseInventoryItem* item);

	UFUNCTION(BlueprintCallable, Server, Unreliable)
	void DropItemServer(ABaseInventoryItem* item);

	UFUNCTION(NetMulticast, Unreliable)
	void SetActorLocAndRotMulticast(ABaseInventoryItem* item, FVector Loc, FRotator Rot);

	UFUNCTION()
	void Overlap(AActor* OverlappedActor, AActor* OtherActor );
	
};
