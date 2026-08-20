// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "TssAIController.h"
#include "TssDummyAnimInstance.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AbilitySystem/TssAbilityInfo.h"
#include "Player/TssCharacterBase.h"
#include "TssEnemyBase.generated.h"

USTRUCT(BlueprintType)
struct FLoot {
	
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> lootAsset;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float spawnWeight;
	
	float adjustedSpawnWeight;
};

UCLASS()
class TWILIGHTSOULSECTOR_API ATssEnemyBase : public ATssCharacterBase {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Base | Behaviours")
	TObjectPtr<UBehaviorTree> behaviourTree; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Base | Behaviours")
	FName hitValueName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Base | Behaviours")
	FName deadValueName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Base | Abilities")
	TArray<TObjectPtr<UTssAbilityInfo>> enemyAbilities;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Base | Loot")
	float lootDropChance;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Base | Loot")
	TArray<FLoot> lootDrops;
	
	//-----------------------------------------------------------------------------------------
	// Protected Fields:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UPROPERTY()
	TObjectPtr<ATssAIController> aiController; 
	
	UPROPERTY(Transient)
	TObjectPtr<UTssDummyAnimInstance> animInstance;
	
	UPROPERTY(BlueprintReadOnly, Category = "Enemy Base")
	TObjectPtr<UBlackboardComponent> blackboardComponent;
	
	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------
	
private:
	
	float totalSpawnWeight;
	
	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaSeconds) override;
	
	//-----------------------------------------------------------------------------------------
	// Blueprint Implemented Events:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy Base")
	void InitBlackboard_BP(); 
	
	//-----------------------------------------------------------------------------------------
	// Protected Methods:
	//-----------------------------------------------------------------------------------------	
	
protected:
	
	virtual FVector GetSocketByIndex_Implementation(int socketIndex) override; 
	virtual void HandleDeath_Implementation() override;
	virtual void HandleIsHit() override;
	
	void SpawnLoot(); 
	
	//-----------------------------------------------------------------------------------------
	// Private Methods:
	//-----------------------------------------------------------------------------------------
	
private:
	
	void EquipAbility(const TObjectPtr<UTssAbilityInfo>& abilityInfo); 
};
