// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "TssAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class TWILIGHTSOULSECTOR_API UTssAttributeSet : public UAttributeSet {	
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Attributes:
	//-----------------------------------------------------------------------------------------
	
public:
	
	// Derived Attributes ---------------------------------------------------------------------
	
	UPROPERTY(BlueprintReadOnly, Category = "Derived Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTssAttributeSet, MaxHealth);	
	
	UPROPERTY(BlueprintReadOnly, Category = "Derived Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UTssAttributeSet, MaxMana);	
	
	UPROPERTY(BlueprintReadOnly, Category = "Derived Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UTssAttributeSet, MaxStamina);	
	
	// Vital Attributes -----------------------------------------------------------------------
	
	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTssAttributeSet, Health);	

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UTssAttributeSet, Mana);
	
	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UTssAttributeSet, Stamina);
	
	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------
	
private: 
	
	bool shouldRefillHealth = false;
	bool shouldRefillMana = false; 
	bool shouldRefillStamina = false; 
	
	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	void FullRestore(); 
	void RestoreHealth(); 
	void RestoreMana(); 
	void RestoreStamina(); 
};
