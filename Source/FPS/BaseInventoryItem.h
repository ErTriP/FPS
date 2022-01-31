#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BaseInventoryItem.generated.h"

class AFPSCharacter;
USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTexture2D* Texture2D;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Discription;

	FInventoryItem()
	{
		Texture2D = nullptr;
		Name = "Unknown";
		Discription = FText::FromString("Unknown");
	}
	
};

UCLASS()
class FPS_API ABaseInventoryItem : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	
public:	
	ABaseInventoryItem();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventoryItem ItemStruct;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Use(AFPSCharacter* Character);

	UFUNCTION(BlueprintCallable)
	UBoxComponent* GetBoxCollision() {return BoxComponent;}

	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetMesh() {return StaticMeshComponent;}

};
