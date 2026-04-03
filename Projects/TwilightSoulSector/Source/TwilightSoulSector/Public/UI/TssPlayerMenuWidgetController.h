// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "TssEvents.h"
#include "Player/TssCharacter.h"
#include "UI/TssWidgetController.h"
#include "TssPlayerMenuWidgetController.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssPlayerMenuWidgetController : public UTssWidgetController {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Events:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	UPROPERTY(BlueprintAssignable)
	FIntDelegate AttributePointsUpdated;
	
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
	void TssCharacter_AttributePointsUpdated(int numPoints); 
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------
	
public:
	
	virtual void BindCallbacksToDependencies() override;
	
	//-----------------------------------------------------------------------------------------
	// Protected Methods:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UFUNCTION(BlueprintCallable)
	void UpdateAttribute(FGameplayTag attributeTag);
};
