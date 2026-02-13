// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Structs.h"
#include "TssAbilitySystemComponent.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssAbilitySystemComponent : public UAbilitySystemComponent {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& startupAbilites);
	void AddCharacterAbility(const TSubclassOf<UGameplayAbility> ability, FGameplayTag montageTag);
	
	void RemoveCharacterAbility(const FGameplayTag abilityTag); 
	
	void AbilityPressed(const FGameplayTag& abilityTag);
	void AbilityHeld(const FGameplayTag& abilityTag); 
	void AbilityReleased(const FGameplayTag& abilityTag);
	
	void ApplySimpleGameplayEffect(TSubclassOf<UGameplayEffect> effect, float level = 1.0f);
	void ApplyDamageEffect(const TSubclassOf<UGameplayEffect> effect, const float damage, const float level = 1.0f);
};
