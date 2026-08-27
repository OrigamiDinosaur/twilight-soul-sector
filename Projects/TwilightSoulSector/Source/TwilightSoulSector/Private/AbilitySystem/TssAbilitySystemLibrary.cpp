// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssAbilitySystemLibrary.h"

#include "GameplayTagContainer.h"
#include "Debug/DebugLog.h"

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

bool UTssAbilitySystemLibrary::GetGameplayTagFromName(FName inName, FGameplayTag& tag) {

	LOGPARAMS("Tag %s", *inName.ToString())
	
	tag = FGameplayTag::RequestGameplayTag(inName);
	return tag.IsValid();	
}

void UTssAbilitySystemLibrary::TryActivateAbilityWithTag(UAbilitySystemComponent* asc, const TSubclassOf<UGameplayAbility> ability, const FGameplayTag tag) {
	
	FGameplayAbilitySpec abilitySpec = FGameplayAbilitySpec(ability, 1); 
	abilitySpec.GetDynamicSpecSourceTags().AddTag(tag); 
	
	asc->GiveAbilityAndActivateOnce(abilitySpec);
}
