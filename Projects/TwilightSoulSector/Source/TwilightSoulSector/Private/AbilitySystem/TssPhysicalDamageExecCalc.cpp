// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssPhysicalDamageExecCalc.h"

#include "AbilitySystem/TssAttributeSet.h"
#include "AbilitySystem/TssGameplayTags.h"
#include "Debug/DebugLog.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/TssCharacterBase.h"

//-----------------------------------------------------------------------------------------
//  Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

UTssPhysicalDamageExecCalc::UTssPhysicalDamageExecCalc() {
	
	DEFINE_ATTRIBUTE_CAPTUREDEF(UTssAttributeSet, PhysicalDamage, Source, false); 
	DEFINE_ATTRIBUTE_CAPTUREDEF(UTssAttributeSet, Resistance, Target, false); 
	
	RelevantAttributesToCapture.Add(PhysicalDamageDef);
	RelevantAttributesToCapture.Add(ResistanceDef); 
}

void UTssPhysicalDamageExecCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const {
	
	const FTssGameplayTags& tags = FTssGameplayTags::Get(); 
	
	const FGameplayEffectSpec& spec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle contextHandle = spec.GetEffectContext();
	
	const FGameplayTagContainer* sourceTags = spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* targetTags = spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters evaluationParameters;
	evaluationParameters.SourceTags = sourceTags;
	evaluationParameters.TargetTags = targetTags;
	
	// get our base damage from our spec. 
	float baseDamage = spec.GetSetByCallerMagnitude(tags.Attributes_Meta_OutgoingDamage, false); 
		
	// get our physical damge from our capture defs.
	float physicalDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(PhysicalDamageDef, evaluationParameters, physicalDamage);
	physicalDamage = FMath::Max(0.0f, physicalDamage); 
	
	// physical damage is a percentage boost
	baseDamage *= 1 + (physicalDamage / 100.0f); 
	
	// get our resistance from our capture defs.
	float resistance = 0.0f; 
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ResistanceDef, evaluationParameters, resistance); 
	resistance = FMath::Max(0.0f, resistance); 
	
	// we're going for a New Vegas DT style resistance.
	// first calculate our resistance compared to our damage. 
	float normalizedResistance = UKismetMathLibrary::NormalizeToRange(resistance, 0.0f, baseDamage);
	normalizedResistance = FMath::Clamp(normalizedResistance, 0.0f, 1.0f); 
	
	// get our damage reduction based on our normalized resistance. 
	const float damageReduction = 1.0f - FMath::Lerp(0.0f, MAX_DAMAGE_REDUCTION, normalizedResistance);
	
	// reduce our damage.
	const float reducedDamage = baseDamage * damageReduction; 
	
	const FGameplayModifierEvaluatedData evaluatedData(UTssAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, reducedDamage);
	OutExecutionOutput.AddOutputModifier(evaluatedData); 
}
