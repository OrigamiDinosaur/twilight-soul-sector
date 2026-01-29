// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "AbilitySystem/TssAbilitySystemComponent.h"
#include "AbilitySystem/TssGameplayTags.h"
#include "Debug/DebugLog.h"
#include "Player/TssCharacterBase.h"

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
	
	if (Attribute == GetStaminaAttribute()) {
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina()); 
	}
}

void UTssAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);
	
	FGameplayAttribute attribute = Data.EvaluatedData.Attribute; 
	
	if (attribute == GetHealthAttribute()) {
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}

	if (attribute == GetManaAttribute()) {
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
	
	if (attribute == GetStaminaAttribute()) {
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina())); 
	}
	
	if (attribute == GetIncomingDamageAttribute()) {
		HandleIncomingDamage(Data.EffectSpec.GetContext().GetOriginalInstigatorAbilitySystemComponent());
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
// Getters / Setters:
//-----------------------------------------------------------------------------------------
	

FGameplayAttribute UTssAttributeSet::GetAttributeFromTag(const FGameplayTag& attributeTag) {

	const FTssGameplayTags tags = FTssGameplayTags::Get(); 
	
	// really wish we could do a switch for gameplay tags but hey ho. 
	
	// derived
	if (attributeTag.MatchesTagExact(tags.Attributes_Derived_MaxHealth)) return GetMaxHealthAttribute();
	if (attributeTag.MatchesTagExact(tags.Attributes_Derived_MaxMana)) return GetMaxManaAttribute();
	if (attributeTag.MatchesTagExact(tags.Attributes_Derived_MaxStamina)) return GetMaxStaminaAttribute();
	
	// vital 
	if (attributeTag.MatchesTagExact(tags.Attributes_Vital_Health)) return GetHealthAttribute();
	if (attributeTag.MatchesTagExact(tags.Attributes_Vital_Mana)) return GetManaAttribute();
	if (attributeTag.MatchesTagExact(tags.Attributes_Vital_Stamina)) return GetStaminaAttribute();
	
	// meta
	if (attributeTag.MatchesTagExact(tags.Attributes_Meta_IncomingDamage)) return GetIncomingDamageAttribute(); 
		
	return FGameplayAttribute(); 
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

//-----------------------------------------------------------------------------------------
// Private Methods:
//-----------------------------------------------------------------------------------------

void UTssAttributeSet::HandleIncomingDamage(const TObjectPtr<UAbilitySystemComponent> asc) {
	
	const float localIncomingDamage = GetIncomingDamage();
	SetIncomingDamage(0.0f); 
	
	if (localIncomingDamage > 0) {
		
		const float newHealth = GetHealth() - localIncomingDamage;
		SetHealth(FMath::Clamp(newHealth, 0.0f, GetMaxHealth()));
		
		if (newHealth <= 0.0f) {
			
			if (const TObjectPtr<ATssCharacterBase> characterBase = Cast<ATssCharacterBase>(asc->AbilityActorInfo->AvatarActor.Get())) {
				characterBase->Die(); 
			}
		}
		else {
			
			FGameplayTagContainer tagContainer;
			tagContainer.AddTag(FTssGameplayTags::Get().Abilities_Shared_HitReact);
			asc->TryActivateAbilitiesByTag(tagContainer); 
		}
	}
}
