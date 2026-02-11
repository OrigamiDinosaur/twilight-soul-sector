// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssMaxStaminaMmc.h"

#include "AbilitySystem/TssAttributeSet.h"
#include "Player/TssCharacterBase.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

UTssMaxStaminaMmc::UTssMaxStaminaMmc() {
		
	// configure our stamina capture. 
	determinationDef.AttributeToCapture = UTssAttributeSet::GetDeterminationAttribute();
	determinationDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	determinationDef.bSnapshot = false;
	
	// configure our might capture
	mightDef.AttributeToCapture = UTssAttributeSet::GetMightAttribute(); 
	mightDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	mightDef.bSnapshot = false; 
	
	// make sure we get our captures. 
	RelevantAttributesToCapture.Add(mightDef); 
	RelevantAttributesToCapture.Add(determinationDef); 
}

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

float UTssMaxStaminaMmc::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const {
	
	// gather tags from source and target. 
	const FGameplayTagContainer* sourceTags = Spec.CapturedSourceTags.GetAggregatedTags(); 
	const FGameplayTagContainer* targetTags = Spec.CapturedSourceTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters evaluationParameters;
	evaluationParameters.SourceTags = sourceTags; 
	evaluationParameters.TargetTags = targetTags; 
	
	// capture our clarity
	float determination = 0.0f;
	GetCapturedAttributeMagnitude(determinationDef, Spec, evaluationParameters, determination);
	determination = FMath::Max<float>(determination, 0.0f); 
	
	// capture our might
	float might = 0.0f; 
	GetCapturedAttributeMagnitude(mightDef, Spec, evaluationParameters, might);
	might = FMath::Max<float>(might, 0.0f); 
	
	int32 characterLevel = 1; 
	
	if (const ATssCharacterBase* characterBase = Cast<ATssCharacterBase>(Spec.GetContext().GetSourceObject())) {
		characterLevel = characterBase->GetCharacterLevel();
	}
	
	return BASE_VALUE + (BONUS_PER_LEVEL * characterLevel) + (determination * DETERMINATION_MULTIPLIER) + (might * MIGHT_MULTIPLIER); 
}
