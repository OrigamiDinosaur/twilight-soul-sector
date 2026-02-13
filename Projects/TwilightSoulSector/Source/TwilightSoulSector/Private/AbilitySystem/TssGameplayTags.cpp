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
	
	// Primary Attributes
	
	instance.Attributes_Primary_Might = tm.AddNativeGameplayTag(FName("Attributes.Primary.Might"), FString("Determines Physical Damage and Contributes to Max Health, and Max Stamina"));
	instance.Attributes_Primary_Clarity = tm.AddNativeGameplayTag(FName("Attributes.Primary.Clarity"), FString("Determines Magical Damage and Contributes to Max Mana, and Max Health"));
	instance.Attributes_Primary_Determination = tm.AddNativeGameplayTag(FName("Attributes.Primary.Determination"), FString("Determines Resistance and Contributes to Max Mana, and Max Stamina"));
	
	// Derived Attributes
	
	instance.Attributes_Derived_MaxHealth = tm.AddNativeGameplayTag(FName("Attributes.Derived.MaxHealth"), FString("Characters Max Health"));
	instance.Attributes_Derived_MaxMana = tm.AddNativeGameplayTag(FName("Attributes.Derived.MaxMana"), FString("Characters Max Mana"));
	instance.Attributes_Derived_MaxStamina = tm.AddNativeGameplayTag(FName("Attributes.Derived.MaxStamina"), FString("Characters Max Stamina"));
	
	instance.Attributes_Derived_PhysicalDamage = tm.AddNativeGameplayTag(FName("Attributes.Derived.PhysicalDamage"), FString("Determines bonus Physical Damage"));
	instance.Attributes_Derived_MagicalDamage = tm.AddNativeGameplayTag(FName("Attributes.Derived.MagicalDamage"), FString("Determines bonus Magical Damage"));
	instance.Attributes_Derived_Resistance = tm.AddNativeGameplayTag(FName("Attributes.Derived.Resistance"), FString("Determines base Damage Resistance"));
	
	// Vital Attributes
	
	instance.Attributes_Vital_Health = tm.AddNativeGameplayTag(FName("Attributes.Vital.Health"), FString("Characters Current Health"));	
	instance.Attributes_Vital_Mana = tm.AddNativeGameplayTag(FName("Attributes.Vital.Mana"), FString("Characters Current Mana"));	
	instance.Attributes_Vital_Stamina = tm.AddNativeGameplayTag(FName("Attributes.Vital.Stamina"), FString("Characters Current Stamina"));	
	
	// Meta Attributes
	
	instance.Attributes_Meta_OutgoingDamage = tm.AddNativeGameplayTag(FName("Attributes.Meta.OutcomingDamage"));
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
	
	// ---------- State  --------------------
	
	instance.State_Player_Equip = tm.AddNativeGameplayTag(FName("State.Player.Equip")); 
} 

