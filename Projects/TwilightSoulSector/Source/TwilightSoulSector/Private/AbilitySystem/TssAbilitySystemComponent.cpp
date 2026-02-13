// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssAbilitySystemComponent.h"

#include "AbilitySystem/TssGameplayTags.h"
#include "Debug/DebugLog.h"

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

void UTssAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& startupAbilites) {
	
	for (const TSubclassOf<UGameplayAbility>& ability : startupAbilites) {
		
		// all starting abilities given at level 1. 
		FGameplayAbilitySpec abilitySpec = FGameplayAbilitySpec(ability, 1);
		GiveAbility(abilitySpec); 
	}
}

void UTssAbilitySystemComponent::AddCharacterAbility(const TSubclassOf<UGameplayAbility> ability, const FGameplayTag montageTag) {
	
	// all starting abilities given at level 1. 
	FGameplayAbilitySpec abilitySpec = FGameplayAbilitySpec(ability, 1);
	abilitySpec.GetDynamicSpecSourceTags().AddTag(montageTag); 
	GiveAbility(abilitySpec); 
}

void UTssAbilitySystemComponent::RemoveCharacterAbility(const FGameplayTag abilityTag) {
	
	FScopedAbilityListLock activeScopeLock(*this); 
	
	FGameplayAbilitySpec* specToRemove = nullptr;
	
	for (FGameplayAbilitySpec& abilitySpec : GetActivatableAbilities()) {		
		if (abilitySpec.Ability.Get()->GetAssetTags().HasTagExact(abilityTag)) specToRemove = &abilitySpec; 
	}
	
	if (specToRemove) {
		ClearAbility(specToRemove->Handle);
	}
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

void UTssAbilitySystemComponent::ApplySimpleGameplayEffect(const TSubclassOf<UGameplayEffect> effect, const float level) {

	const FGameplayEffectContextHandle contextHandle = MakeEffectContext(); 
	const FGameplayEffectSpecHandle specHandle = MakeOutgoingSpec(effect, level, contextHandle); 
	ApplyGameplayEffectSpecToSelf(*specHandle.Data); 	
}

void UTssAbilitySystemComponent::ApplyDamageEffect(const TSubclassOf<UGameplayEffect> effect, const float damage, const float level) {
	
	const FGameplayEffectContextHandle contextHandle = MakeEffectContext();
	const FGameplayEffectSpecHandle specHandle = MakeOutgoingSpec(effect, level, contextHandle); 
	FGameplayEffectSpec* spec = specHandle.Data.Get();
	spec->SetSetByCallerMagnitude(FTssGameplayTags::Get().Attributes_Meta_OutgoingDamage, damage);
	ApplyGameplayEffectSpecToSelf(*spec); 
}
