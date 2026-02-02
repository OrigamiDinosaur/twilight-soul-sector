// Origami Dinosaur Creations 2026 (C)

#include "UI/TssCharacterWidgetController.h"

#include "Debug/DebugLog.h"

//-----------------------------------------------------------------------------------------
// Event Handlers:
//-----------------------------------------------------------------------------------------

void UTssCharacterWidgetController::TssCharacter_PrimaryAbilityAssigned(UTssAbilityInfo* info) {
	if (PrimaryAbilityAssigned.IsBound()) PrimaryAbilityAssigned.Broadcast(info); 
}

void UTssCharacterWidgetController::TssCharacter_PrimaryAbilityUnassigned() {
	if (PrimaryAbilityUnassigned.IsBound()) PrimaryAbilityUnassigned.Broadcast(); 
}

void UTssCharacterWidgetController::TssCharacter_SecondaryAbilityAssigned(UTssAbilityInfo* info) {
	if (SecondaryAbilityAssigned.IsBound()) SecondaryAbilityAssigned.Broadcast(info); 
}

void UTssCharacterWidgetController::TssCharacter_SecondaryAbilityUnassigned() {
	if (SecondaryAbilityUnassigned.IsBound()) SecondaryAbilityUnassigned.Broadcast(); 
}

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

void UTssCharacterWidgetController::BroadcastInitialValues() {
	Super::BroadcastInitialValues();
	
	if (!tssCharacter) {
		LOGERROR("Tss Character not assigned in Character Widget Controller");
	}
	else {
		
		tssCharacter->PrimaryAbilityAssigned.AddDynamic(this, &UTssCharacterWidgetController::TssCharacter_PrimaryAbilityAssigned);
		tssCharacter->PrimaryAbilityUnassigned.AddDynamic(this, &UTssCharacterWidgetController::TssCharacter_PrimaryAbilityUnassigned);
		tssCharacter->SecondaryAbilityAssigned.AddDynamic(this, &UTssCharacterWidgetController::TssCharacter_SecondaryAbilityAssigned);
		tssCharacter->SecondaryAbilityUnassigned.AddDynamic(this, &UTssCharacterWidgetController::TssCharacter_SecondaryAbilityUnassigned); 
	}
}
