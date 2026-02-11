// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "TssMaxStaminaMmc.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssMaxStaminaMmc : public UGameplayModMagnitudeCalculation {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Constants:
	//-----------------------------------------------------------------------------------------
	
private:

	const float BASE_VALUE = 40.0f;
	const float BONUS_PER_LEVEL = 10.0f; 
	const float DETERMINATION_MULTIPLIER = 2.5f;
	const float MIGHT_MULTIPLIER = 2.5f;
	
	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------

private:

	FGameplayEffectAttributeCaptureDefinition determinationDef;
	FGameplayEffectAttributeCaptureDefinition mightDef;
	
	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------

public:

	UTssMaxStaminaMmc();

	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------

public:

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
