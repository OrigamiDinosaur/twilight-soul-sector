// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssAbilitySystemComponent.h"

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

void UTssAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& startupAbilites) {
	
	for (const TSubclassOf<UGameplayAbility> ability : startupAbilites) {
		
		// all starting abilities given at level 1. 
		FGameplayAbilitySpec abilitySpec = FGameplayAbilitySpec(ability, 1); 
		GiveAbility(abilitySpec); 		
	}
}

void UTssAbilitySystemComponent::AbilityPressed(const FGameplayTag& abilityTag) {
	if (!abilityTag.IsValid()) return; 
	
	FScopedAbilityListLock activeScopeLock(*this); 
	
	for (FGameplayAbilitySpec& abilitySpec : GetActivatableAbilities()) {
		
		TArray<FGameplayTag> gameplayTags;
		abilitySpec.Ability.Get()->AbilityTags.GetGameplayTagArray(gameplayTags); 
				
		if (abilitySpec.Ability.Get()->AbilityTags.HasTagExact(abilityTag)) {
			AbilitySpecInputPressed(abilitySpec); 
		}
	}
}

void UTssAbilitySystemComponent::AbilityHeld(const FGameplayTag& abilityTag) {
	if (!abilityTag.IsValid()) return; 
	
	FScopedAbilityListLock activeScopeLock(*this); 
	
	for (FGameplayAbilitySpec& abilitySpec : GetActivatableAbilities()) {
		
		if (abilitySpec.Ability.Get()->AbilityTags.HasTagExact(abilityTag)) {
			AbilitySpecInputPressed(abilitySpec);
			if (!abilitySpec.IsActive()) TryActivateAbility(abilitySpec.Handle); 
		}
	}
}

void UTssAbilitySystemComponent::AbilityReleased(const FGameplayTag& abilityTag) {
	if (!abilityTag.IsValid()) return; 
	
	FScopedAbilityListLock activeScopeLock(*this); 
	
	for (FGameplayAbilitySpec& abilitySpec : GetActivatableAbilities()) {
		
		if (abilitySpec.Ability.Get()->AbilityTags.HasTagExact(abilityTag) && abilitySpec.IsActive()) {
			AbilitySpecInputReleased(abilitySpec);	
		}
	}
}

void UTssAbilitySystemComponent::ApplySimpleGameplayEffect(TSubclassOf<UGameplayEffect> effect, float level) {

	const FGameplayEffectContextHandle contextHandle = MakeEffectContext(); 
	const FGameplayEffectSpecHandle specHandle = MakeOutgoingSpec(effect, level, contextHandle); 
	ApplyGameplayEffectSpecToSelf(*specHandle.Data); 	
}
