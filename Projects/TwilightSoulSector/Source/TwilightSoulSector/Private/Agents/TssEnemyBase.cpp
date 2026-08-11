// Origami Dinosaur Creations 2026 (C)

#include "Agents/TssEnemyBase.h"

#include "AbilitySystem/TssGameplayTags.h"
#include "Agents/TssDummyAnimInstance.h"
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
	
	animInstance = Cast<UTssDummyAnimInstance>(GetMesh()->GetAnimInstance()); 
	
	if (!animInstance) {
		LOGERROR("AnimInstance not found in TssDummy");
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

void ATssEnemyBase::HandleDeath_Implementation() {
	if (animInstance) animInstance->SetShouldDie(true); 
	
	aiController->GetBlackboardComponent()->SetValueAsBool(deadValueName, true); 
	
	SpawnExp();
	
	SetActorEnableCollision(false); 
}

void ATssEnemyBase::HandleIsHit() {
	
	aiController->GetBlackboardComponent()->SetValueAsBool(hitValueName, isHit); 
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
