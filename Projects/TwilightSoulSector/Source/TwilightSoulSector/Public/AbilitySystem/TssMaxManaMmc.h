// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "TssMaxManaMmc.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssMaxManaMmc : public UGameplayModMagnitudeCalculation {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Constants:
	//-----------------------------------------------------------------------------------------
	
private:

	const float BASE_VALUE = 40.0f;
	const float BONUS_PER_LEVEL = 10.0f; 
	const float CLARITY_MULTIPLIER = 2.5f;
	const float DETERMINATION_MULTIPLIER = 2.5f;
	
	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------

private:

	FGameplayEffectAttributeCaptureDefinition clarityDef;
	FGameplayEffectAttributeCaptureDefinition determinationDef;
	
	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------

public:

	UTssMaxManaMmc();

	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------

public:

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
