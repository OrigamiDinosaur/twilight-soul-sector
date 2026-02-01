// Origami Dinosaur Creations 2026 (C)

#include "UI/TssHUD.h"

#include "Debug/DebugLog.h"
#include "UI/TssCharacterWidgetController.h"

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

void ATssHUD::InitHud(TObjectPtr<UTssAbilitySystemComponent> asc, TObjectPtr<UTssAttributeSet> as, TObjectPtr<ATssCharacter> character) {
	
	// create our overlay widget 
	overlayWidget = Cast<UTssPlayerOverlayWidget>(CreateWidget<UUserWidget>(GetWorld(), overlayWidgetAsset));
	
	if (!overlayWidget) {
		LOGERROR("Overlay Widget not found in Tss HUD");
	}
	else {
		
		overlayWidgetController = NewObject<UTssCharacterWidgetController>(this, overlayWidgetControllerAsset); 
		overlayWidgetController->SetAbilitySystemComponent(asc);
		overlayWidgetController->SetAttributeSet(as); 
		overlayWidgetController->SetTssCharacter(character); 
		overlayWidgetController->BindCallbacksToDependencies();
		
		overlayWidget->SetWidgetController(overlayWidgetController); 
		overlayWidget->AddToViewport(); 
		overlayWidgetController->BroadcastInitialValues(); 
	}
}
