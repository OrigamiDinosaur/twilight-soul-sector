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
	
	void AddCharacterAbilities(const TArray<FTaggedAbility>& startupAbilites);
	void AddCharacterAbility(const FTaggedAbility& ability); 
	
	void AbilityPressed(const FGameplayTag& abilityTag);
	void AbilityHeld(const FGameplayTag& abilityTag); 
	void AbilityReleased(const FGameplayTag& abilityTag);
	
	void ApplySimpleGameplayEffect(TSubclassOf<UGameplayEffect> effect, float level = 1.0f);
};
