// Origami Dinosaur Creations 2026 (C)

#include "UI/TssPlayerMenuWidgetController.h"

#include "Debug/DebugLog.h"

//-----------------------------------------------------------------------------------------
// Event Handlers:
//-----------------------------------------------------------------------------------------

void UTssPlayerMenuWidgetController::TssCharacter_AttributePointsUpdated(const int numPoints) {
	if (AttributePointsUpdated.IsBound()) AttributePointsUpdated.Broadcast(numPoints);
}

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------
	
void UTssPlayerMenuWidgetController::BindCallbacksToDependencies() {
	Super::BindCallbacksToDependencies();
	
	if (!tssCharacter) {
		LOGERROR("Tss Character not assigned in Character Widget Controller");
	}
	else {		
		tssCharacter->AttributePointsUpdated.AddDynamic(this, &UTssPlayerMenuWidgetController::TssCharacter_AttributePointsUpdated);
	}
}

//-----------------------------------------------------------------------------------------
// Protected Methods:
//-----------------------------------------------------------------------------------------

void UTssPlayerMenuWidgetController::UpdateAttribute(const FGameplayTag attributeTag) {
	if (tssCharacter) tssCharacter->UpgradeAttribute(attributeTag);
}
