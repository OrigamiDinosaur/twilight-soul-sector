// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssMaxHealthMmc.h"
#include "AbilitySystem/TssAttributeSet.h"
#include "Player/TssCharacterBase.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

UTssMaxHealthMmc::UTssMaxHealthMmc() {
		// configure our might capture
	mightDef.AttributeToCapture = UTssAttributeSet::GetMightAttribute(); 
	mightDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	mightDef.bSnapshot = false; 
	
	// configure our clarity capture. 
	clarityDef.AttributeToCapture = UTssAttributeSet::GetClarityAttribute();
	clarityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	clarityDef.bSnapshot = false;
	
	// make sure we get our captures. 
	RelevantAttributesToCapture.Add(mightDef); 
	RelevantAttributesToCapture.Add(clarityDef); 
}

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

float UTssMaxHealthMmc::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const {
	
	// gather tags from source and target. 
	const FGameplayTagContainer* sourceTags = Spec.CapturedSourceTags.GetAggregatedTags(); 
	const FGameplayTagContainer* targetTags = Spec.CapturedSourceTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters evaluationParameters;
	evaluationParameters.SourceTags = sourceTags; 
	evaluationParameters.TargetTags = targetTags; 
	
	// capture our might
	float might = 0.0f; 
	GetCapturedAttributeMagnitude(mightDef, Spec, evaluationParameters, might);
	might = FMath::Max<float>(might, 0.0f); 
	
	// capture our clarity
	float clarity = 0.0f;
	GetCapturedAttributeMagnitude(clarityDef, Spec, evaluationParameters, clarity);
	clarity = FMath::Max<float>(clarity, 0.0f); 
	
	int32 characterLevel = 1; 
	
	if (const ATssCharacterBase* characterBase = Cast<ATssCharacterBase>(Spec.GetContext().GetSourceObject())) {
		characterLevel = characterBase->GetCharacterLevel();
	}
	
	return BASE_VALUE + (BONUS_PER_LEVEL * characterLevel) + (might * MIGHT_MULTIPLIER) + (clarity * CLARITY_MULTIPLIER); 
}
