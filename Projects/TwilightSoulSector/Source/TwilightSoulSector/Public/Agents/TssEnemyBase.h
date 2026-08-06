// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "TssAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AbilitySystem/TssAbilityInfo.h"
#include "Player/TssCharacterBase.h"
#include "TssEnemyBase.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API ATssEnemyBase : public ATssCharacterBase {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Base | Behaviours")
	TObjectPtr<UBehaviorTree> behaviourTree; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Base | Abilities")
	TArray<TObjectPtr<UTssAbilityInfo>> enemyAbilities;
	
	//-----------------------------------------------------------------------------------------
	// Protected Fields:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UPROPERTY()
	TObjectPtr<ATssAIController> aiController; 
	
	UPROPERTY(BlueprintReadOnly, Category = "Enemy Base")
	TObjectPtr<UBlackboardComponent> blackboardComponent;
	
	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	virtual void PossessedBy(AController* NewController) override;
	
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
	
	//-----------------------------------------------------------------------------------------
	// Private Methods:
	//-----------------------------------------------------------------------------------------
	
private:
	
	void EquipAbility(const TObjectPtr<UTssAbilityInfo>& abilityInfo); 
};
