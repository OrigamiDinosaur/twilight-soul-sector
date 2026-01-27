// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssGameplayTags.h"
#include "GameplayTagsManager.h"

FTssGameplayTags FTssGameplayTags::instance;

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

void FTssGameplayTags::InitializeGameplayTags() {
	
	UGameplayTagsManager& tm = UGameplayTagsManager::Get();
	
	// ---------- Attributes --------------------
	
	// Derived Attributes
	
	instance.Attributes_Derived_MaxHealth = tm.AddNativeGameplayTag(FName("Attributes.Derived.MaxHealth"), FString("Characters Max Health"));
	instance.Attributes_Derived_MaxMana = tm.AddNativeGameplayTag(FName("Attributes.Derived.MaxMana"), FString("Characters Max Mana"));
	instance.Attributes_Derived_MaxStamina = tm.AddNativeGameplayTag(FName("Attributes.Derived.MaxStamina"), FString("Characters Max Stamina"));
	
	// Vital Attributes
	
	instance.Attributes_Vital_Health = tm.AddNativeGameplayTag(FName("Attributes.Vital.Health"), FString("Characters Current Health"));	
	instance.Attributes_Vital_Mana = tm.AddNativeGameplayTag(FName("Attributes.Vital.Mana"), FString("Characters Current Mana"));	
	instance.Attributes_Vital_Stamina = tm.AddNativeGameplayTag(FName("Attributes.Vital.Stamina"), FString("Characters Current Stamina"));	
} 

