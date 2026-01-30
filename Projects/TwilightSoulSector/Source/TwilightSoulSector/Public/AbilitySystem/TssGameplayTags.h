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
	
	// Derived 
	
	FGameplayTag Attributes_Derived_MaxHealth;
	FGameplayTag Attributes_Derived_MaxMana; 
	FGameplayTag Attributes_Derived_MaxStamina;
	
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
