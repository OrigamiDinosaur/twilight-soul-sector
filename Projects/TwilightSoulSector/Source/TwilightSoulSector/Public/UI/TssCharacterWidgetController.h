// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "Player/TssCharacter.h"
#include "UI/TssWidgetController.h"
#include "TssCharacterWidgetController.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssCharacterWidgetController : public UTssWidgetController {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Events:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	UPROPERTY(BlueprintAssignable)
	FAbilityInfoDelegate PrimaryAbilityAssigned;
	
	UPROPERTY(BlueprintAssignable)
	FActionDelegate PrimaryAbilityUnassigned;
	
	UPROPERTY(BlueprintAssignable)
	FAbilityInfoDelegate SecondaryAbilityAssigned;
	
	UPROPERTY(BlueprintAssignable)
	FActionDelegate SecondaryAbilityUnassigned;
	
	UPROPERTY(BlueprintAssignable)
	FActionDelegate AbilityEquipAvailable; 
	
	UPROPERTY(BlueprintAssignable)
	FActionDelegate AbilityEquipUnavailable; 
	
	UPROPERTY(BlueprintAssignable)
	FFloatDelegate ExpUpdated;
	
	UPROPERTY(BlueprintAssignable)
	FIntDelegate LevelUpdated;
	
	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------
	
private: 
	
	UPROPERTY(Transient)
	TObjectPtr<ATssCharacter> tssCharacter;
	
	//-----------------------------------------------------------------------------------------
	// Getters / Setters:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	void SetTssCharacter(ATssCharacter* inCharacter) { tssCharacter = inCharacter; }
	
	//-----------------------------------------------------------------------------------------
	// Event Handlers:
	//-----------------------------------------------------------------------------------------
	
private:
	
	UFUNCTION()
	void TssCharacter_PrimaryAbilityAssigned(UTssAbilityInfo* info);
	
	UFUNCTION()
	void TssCharacter_PrimaryAbilityUnassigned(); 
	
	UFUNCTION()
	void TssCharacter_SecondaryAbilityAssigned(UTssAbilityInfo* info); 
	
	UFUNCTION()
	void TssCharacter_SecondaryAbilityUnassigned(); 
	
	UFUNCTION()
	void TssCharacter_AbilityEquipAvailable();
	
	UFUNCTION()
	void TssCharacter_AbilityEquipUnavailable(); 
	
	UFUNCTION()
	void TssCharacter_ExpUpdated(float normalizedExp);
	
	UFUNCTION()
	void TssCharacter_LevelUpdated(int level); 
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------
	
public:
	
	virtual void BindCallbacksToDependencies() override;
};
