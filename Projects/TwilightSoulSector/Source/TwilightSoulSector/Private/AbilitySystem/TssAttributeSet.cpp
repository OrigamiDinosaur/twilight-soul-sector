// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Debug/DebugLog.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

void UTssAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute()) {
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth()); 
	}
	
	if (Attribute == GetManaAttribute()) {
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
	
	if (Attribute == GetMaxStaminaAttribute()) {
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina()); 
	}
}

void UTssAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute()) {
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute()) {
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
	
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute()) {
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina())); 
	}
}

void UTssAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) {
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == GetMaxHealthAttribute() && shouldRefillHealth) {
		RestoreHealth(); 
		shouldRefillHealth = false; 
	}
	
	if (Attribute == GetMaxManaAttribute() && shouldRefillMana) {
		RestoreMana();
		shouldRefillMana = false; 
	}
	
	if (Attribute == GetMaxStaminaAttribute() && shouldRefillStamina) {
		RestoreStamina();
		shouldRefillStamina = false; 
	}
}

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

void UTssAttributeSet::FullRestore() {

	RestoreHealth(); 
	RestoreMana();
	RestoreStamina();
}

void UTssAttributeSet::RestoreHealth() {	
	SetHealth(GetMaxHealth()); 	
}

void UTssAttributeSet::RestoreMana() {
	SetMana(GetMaxHealth());
}

void UTssAttributeSet::RestoreStamina() {
	 SetStamina(GetMaxStamina()); 
}
