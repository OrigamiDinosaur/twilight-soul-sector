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
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------
	
public:
	
	virtual void BroadcastInitialValues() override;
};
