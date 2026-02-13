// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "TssMagicalDamageExecCalc.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssMagicalDamageExecCalc : public UGameplayEffectExecutionCalculation {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	//  Constants:
	//-----------------------------------------------------------------------------------------
	
private:
	
	const float MAX_DAMAGE_REDUCTION = 0.75f;
	
	//-----------------------------------------------------------------------------------------
	//  Private Properties:
	//-----------------------------------------------------------------------------------------
	
private: 
	
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicalDamage); 
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance); 
	
	//-----------------------------------------------------------------------------------------
	//  Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------

public:
	
	UTssMagicalDamageExecCalc();
	
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
