// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssGameplayAbility.h"

#include "AbilitySystem/TssAttributeSet.h"

float UTssGameplayAbility::GetCost(const FGameplayAttribute& costAttribute, const float level) const {
	
	float cost = 0;

	// const FGameplayAttribute costAttribute = UTssAttributeSet::GetAttributeFromTag(attributeTag); 
	
	// get our cost gameplay effect, iterate over its modifiers, and set our cost if one exists that matches our attribute.
	if (const UGameplayEffect* costEffet = GetCostGameplayEffect()) {		
		for (FGameplayModifierInfo mod : costEffet->Modifiers) {			
			if (mod.Attribute == costAttribute) {
				
				mod.ModifierMagnitude.GetStaticMagnitudeIfPossible(level, cost); 
				break;
			}
		}
	}
	
	return cost; 
}

float UTssGameplayAbility::GetManaCost(const float level) const {	
	return GetCost(UTssAttributeSet::GetManaAttribute(), level);
}

float UTssGameplayAbility::GetStaminaCost(const float level) const {
	return GetCost(UTssAttributeSet::GetStaminaAttribute(), level); 
}

float UTssGameplayAbility::GetHealthCost(const float level) const {
	return GetCost(UTssAttributeSet::GetHealthAttribute(), level); 
}

float UTssGameplayAbility::GetCooldown(const float level) const {
	
	float cooldown = 0; 
	
	if (const UGameplayEffect* cooldownEffect = GetCooldownGameplayEffect()) {		
		cooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(level, cooldown); 
	}
	
	return cooldown;
}
