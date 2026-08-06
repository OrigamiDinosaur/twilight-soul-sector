// Origami Dinosaur Creations 2026 (C)

#include "Agents/TssEnemyBase.h"

#include "AbilitySystem/TssGameplayTags.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Debug/DebugLog.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

void ATssEnemyBase::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);
	
	// cache our controller. 
	aiController = Cast<ATssAIController>(NewController); 
	
	if (!aiController) {
		LOGERROR("AI Controller not found!");
	}
	else {
		
		// initialize our blackoard.
		blackboardComponent = aiController->GetBlackboardComponent();
		blackboardComponent->InitializeBlackboard(*behaviourTree->BlackboardAsset); 
		
		// do any blueprint initialization.
		InitBlackboard_BP();
		
		// run our behaviour.
		aiController->RunBehaviorTree(behaviourTree); 
	}	
	
	for (const TObjectPtr<UTssAbilityInfo>& info : enemyAbilities) {
		EquipAbility(info);
	}
}

//-----------------------------------------------------------------------------------------
// Protected Methods:
//-----------------------------------------------------------------------------------------

FVector ATssEnemyBase::GetSocketByIndex_Implementation(const int socketIndex) {
	return GetMesh()->GetSocketLocation(sockets[socketIndex]); 
}

//-----------------------------------------------------------------------------------------
// Private Methods:
//-----------------------------------------------------------------------------------------

void ATssEnemyBase::EquipAbility(const TObjectPtr<UTssAbilityInfo>& abilityInfo) {
	
	const FTssGameplayTags tags = FTssGameplayTags::Get();
	
	FGameplayTag montageTag = abilityInfo->montageTag;
	
	if (montageTag == tags.Montage_Arms) {
		montageTag = tags.Montage_Arms_Primary; 
	}
	
	abilitySystemComponent->AddCharacterAbility(abilityInfo->ability, montageTag); 
}
