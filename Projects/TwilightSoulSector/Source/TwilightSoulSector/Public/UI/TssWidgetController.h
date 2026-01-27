// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/TssAbilitySystemComponent.h"
#include "AbilitySystem/TssAttributeSet.h"
#include "UObject/NoExportTypes.h"
#include "TssWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttributeChangedSignature, FGameplayTag, tag, float, newValue);

UCLASS(BlueprintType, Blueprintable)
class TWILIGHTSOULSECTOR_API UTssWidgetController : public UObject {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Events:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	UPROPERTY(BlueprintAssignable)
	FAttributeChangedSignature AttributeChangedDelegate;
	
	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------
	
private: 
	
	UPROPERTY(Transient)
	TObjectPtr<UTssAbilitySystemComponent> abilitySystemComponent; 
	
	UPROPERTY(Transient)
	TObjectPtr<UTssAttributeSet> attributeSet; 
		
	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Tss Widget Controller")
	FGameplayTagContainer tagsToListenFor;
	
	//-----------------------------------------------------------------------------------------
	// Getters / Setters:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	void SetAbilitySystemComponent(UTssAbilitySystemComponent* inAsc) { abilitySystemComponent = inAsc; }
	void SetAttributeSet(const TObjectPtr<UTssAttributeSet> inAs) { attributeSet = inAs; }
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies(); 
	
	//-----------------------------------------------------------------------------------------
	// Private Methods:
	//-----------------------------------------------------------------------------------------
	
private:
	
	void BroadcastAttributeChange(FGameplayTag attributeTag); 
};
