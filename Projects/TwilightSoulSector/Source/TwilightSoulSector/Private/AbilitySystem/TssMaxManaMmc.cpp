// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssMaxManaMmc.h"
#include "AbilitySystem/TssAttributeSet.h"
#include "Debug/DebugLog.h"
#include "Player/TssCharacterBase.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

UTssMaxManaMmc::UTssMaxManaMmc() {
		
	// configure our clarity capture. 
	clarityDef.AttributeToCapture = UTssAttributeSet::GetClarityAttribute();
	clarityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	clarityDef.bSnapshot = false;
	
	// configure our stamina capture. 
	determinationDef.AttributeToCapture = UTssAttributeSet::GetDeterminationAttribute();
	determinationDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	determinationDef.bSnapshot = false;
		
	// make sure we get our captures. 
	RelevantAttributesToCapture.Add(clarityDef);
	RelevantAttributesToCapture.Add(determinationDef); 
}

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

float UTssMaxManaMmc::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const {
	
	// gather tags from source and target. 
	const FGameplayTagContainer* sourceTags = Spec.CapturedSourceTags.GetAggregatedTags(); 
	const FGameplayTagContainer* targetTags = Spec.CapturedSourceTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters evaluationParameters;
	evaluationParameters.SourceTags = sourceTags; 
	evaluationParameters.TargetTags = targetTags; 
		
	// capture our clarity
	float clarity = 0.0f;
	GetCapturedAttributeMagnitude(clarityDef, Spec, evaluationParameters, clarity);
	clarity = FMath::Max<float>(clarity, 0.0f); 
		
	// capture our might
	float determination = 0.0f; 
	GetCapturedAttributeMagnitude(determinationDef, Spec, evaluationParameters, determination);
	determination = FMath::Max<float>(determination, 0.0f); 
	
	int32 characterLevel = 1; 
	
	if (const ATssCharacterBase* characterBase = Cast<ATssCharacterBase>(Spec.GetContext().GetSourceObject())) {
		characterLevel = characterBase->GetCharacterLevel();
	}
	
	return BASE_VALUE + (BONUS_PER_LEVEL * characterLevel) + (determination * DETERMINATION_MULTIPLIER) + (clarity * CLARITY_MULTIPLIER); 
}
