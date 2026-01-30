// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssAbilitySystemComponent.h"

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

void UTssAbilitySystemComponent::AddCharacterAbilities(const TArray<FTaggedAbility>& startupAbilites) {
	
	for (const FTaggedAbility& ability : startupAbilites) {
		AddCharacterAbility(ability); 			
	}
}

void UTssAbilitySystemComponent::AddCharacterAbility(const FTaggedAbility& ability) {

	// all starting abilities given at level 1. 
	FGameplayAbilitySpec abilitySpec = FGameplayAbilitySpec(ability.ability, 1);
	abilitySpec.GetDynamicSpecSourceTags().AddTag(ability.tag); 
	GiveAbility(abilitySpec); 	
}

void UTssAbilitySystemComponent::AbilityPressed(const FGameplayTag& abilityTag) {
	if (!abilityTag.IsValid()) return; 
	
	FScopedAbilityListLock activeScopeLock(*this); 
	
	for (FGameplayAbilitySpec& abilitySpec : GetActivatableAbilities()) {
		
		TArray<FGameplayTag> gameplayTags;
		abilitySpec.Ability.Get()->GetAssetTags().GetGameplayTagArray(gameplayTags); 
				
		if (abilitySpec.Ability.Get()->GetAssetTags().HasTagExact(abilityTag)) {
			AbilitySpecInputPressed(abilitySpec); 
		}
	}
}

void UTssAbilitySystemComponent::AbilityHeld(const FGameplayTag& abilityTag) {
	if (!abilityTag.IsValid()) return; 
	
	FScopedAbilityListLock activeScopeLock(*this); 
	
	for (FGameplayAbilitySpec& abilitySpec : GetActivatableAbilities()) {
		
		if (abilitySpec.Ability.Get()->GetAssetTags().HasTagExact(abilityTag)) {
			AbilitySpecInputPressed(abilitySpec);
			if (!abilitySpec.IsActive()) TryActivateAbility(abilitySpec.Handle); 
		}
	}
}

void UTssAbilitySystemComponent::AbilityReleased(const FGameplayTag& abilityTag) {
	if (!abilityTag.IsValid()) return; 
	
	FScopedAbilityListLock activeScopeLock(*this); 
	
	for (FGameplayAbilitySpec& abilitySpec : GetActivatableAbilities()) {
		
		if (abilitySpec.Ability.Get()->GetAssetTags().HasTagExact(abilityTag) && abilitySpec.IsActive()) {
			AbilitySpecInputReleased(abilitySpec);	
		}
	}
}

void UTssAbilitySystemComponent::ApplySimpleGameplayEffect(TSubclassOf<UGameplayEffect> effect, float level) {

	const FGameplayEffectContextHandle contextHandle = MakeEffectContext(); 
	const FGameplayEffectSpecHandle specHandle = MakeOutgoingSpec(effect, level, contextHandle); 
	ApplyGameplayEffectSpecToSelf(*specHandle.Data); 	
}
