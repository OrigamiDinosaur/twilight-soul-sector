// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TssGameplayAbility.h"
#include "TssAreaGameplayAbility.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssAreaGameplayAbility : public UTssGameplayAbility {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------

protected: 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Area Ability | References")
	TSubclassOf<UGameplayEffect> effectToApply;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Area Ability | Effect")
	float radius;
	
	//-----------------------------------------------------------------------------------------
	// Protected Methods:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectInRadius(); 
	
	UFUNCTION(BlueprintCallable)
	void ApplyDamageInRadius(float damage); 
};
