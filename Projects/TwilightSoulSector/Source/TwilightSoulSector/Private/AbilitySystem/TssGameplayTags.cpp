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
	
	// Meta Attributes
	
	instance.Attributes_Meta_IncomingDamage = tm.AddNativeGameplayTag(FName("Attributes.Meta.IncomingDamage"));
	
	// ---------- Abilities --------------------
	
	instance.Abilities_Shared_HitReact = tm.AddNativeGameplayTag(FName("Abilities.Shared.HitReact"));

	// ---------- Input --------------------

	instance.Input_Passive = tm.AddNativeGameplayTag(FName("Input.Passive"));

	instance.Input_Active = tm.AddNativeGameplayTag(FName("Input.Active"));
	instance.Input_Active_Primary = tm.AddNativeGameplayTag(FName("Input.Active.Primary"));
	instance.Input_Active_Secondary = tm.AddNativeGameplayTag(FName("Input.Active.Secondary"));
	
	// ---------- Montages --------------------
	
	instance.Montage = tm.AddNativeGameplayTag(FName("Montage"));
	instance.Montage_Arms = tm.AddNativeGameplayTag(FName("Montage.Arms")); 
	instance.Montage_Arms_Primary = tm.AddNativeGameplayTag(FName("Montage.Arms.Primary")); 
	instance.Montage_Arms_Secondary = tm.AddNativeGameplayTag(FName("Montage.Arms.Secondary")); 
	
	instance.Montage_Area = tm.AddNativeGameplayTag(FName("Montage.Area")); 
} 

