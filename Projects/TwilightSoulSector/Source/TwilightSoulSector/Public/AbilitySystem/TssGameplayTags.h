// Origami Dinosaur Creations 2026 (C)

// ReSharper disable CppInconsistentNaming
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FTssGameplayTags {
	
	//-----------------------------------------------------------------------------------------
	// Public Properties:
	//-----------------------------------------------------------------------------------------

public:
	
	// Attributes -----------------------------------------------------------------------------
	
	// Primary
	
	FGameplayTag Attributes_Primary_Might;
	FGameplayTag Attributes_Primary_Clarity;
	FGameplayTag Attributes_Primary_Determination;
	
	// Derived 
	
	FGameplayTag Attributes_Derived_MaxHealth;
	FGameplayTag Attributes_Derived_MaxMana; 
	FGameplayTag Attributes_Derived_MaxStamina;
	
	FGameplayTag Attributes_Derived_PhysicalDamage;
	FGameplayTag Attributes_Derived_MagicalDamage;
	FGameplayTag Attributes_Derived_Resistance;	
	
	// Vital 
	
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana; 
	FGameplayTag Attributes_Vital_Stamina;
	
	// Meta
	
	FGameplayTag Attributes_Meta_IncomingDamage;
	
	// Abilities ------------------------------------------------------------------------------
	
	FGameplayTag Abilities_Shared_HitReact;

	// Input ----------------------------------------------------------------------------------

	FGameplayTag Input_Passive;

	FGameplayTag Input_Active;
	FGameplayTag Input_Active_Primary;
	FGameplayTag Input_Active_Secondary; 
	
	// Montages -------------------------------------------------------------------------------
	
	FGameplayTag Montage;
	
	FGameplayTag Montage_Arms;
	FGameplayTag Montage_Arms_Primary; 
	FGameplayTag Montage_Arms_Secondary; 
	
	FGameplayTag Montage_Area; 
	
	// State ----------------------------------------------------------------------------------

	FGameplayTag State_Player_Equip; 
	
	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------
	
private: 
	
	static FTssGameplayTags instance; 
	
	//-----------------------------------------------------------------------------------------
	// Getters / Setters:
	//-----------------------------------------------------------------------------------------

public:

	static const FTssGameplayTags& Get() { return instance; };
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------

public:

	static void InitializeGameplayTags(); 
};
