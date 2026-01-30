// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Player/TssCharacterBase.h"
#include "TssGameplayAbility.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssGameplayAbility : public UGameplayAbility {
	GENERATED_BODY()

	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------

private:

	UPROPERTY(Transient)
	TObjectPtr<ATssCharacterBase> characterBase;

	//-----------------------------------------------------------------------------------------
	// Protected Methods:
	//-----------------------------------------------------------------------------------------
	
protected:

	UFUNCTION(BlueprintPure)
	ATssCharacterBase* GetCharacterBase();

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetAbilityMontage(); 
	
	float GetCost(const FGameplayAttribute& costAttribute, const float level = 1.0f) const;
	float GetManaCost(float level = 1.0f) const; 
	float GetStaminaCost(float level = 1.0f) const; 
	float GetHealthCost(float level = 1.0f) const;
	float GetCooldown(float level = 1.0f) const;
};
