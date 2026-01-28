// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TssGameplayAbility.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssGameplayAbility : public UGameplayAbility {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Protected Methods:
	//-----------------------------------------------------------------------------------------
	
protected: 
	
	float GetCost(const FGameplayAttribute& costAttribute, const float level = 1.0f) const;
	float GetManaCost(float level = 1.0f) const; 
	float GetStaminaCost(float level = 1.0f) const; 
	float GetHealthCost(float level = 1.0f) const;
	float GetCooldown(float level = 1.0f) const;
};
