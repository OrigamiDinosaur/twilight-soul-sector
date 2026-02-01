// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "TssCharacterWidgetController.h"
#include "TssPlayerOverlayWidget.h"
#include "GameFramework/HUD.h"
#include "TssHUD.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API ATssHUD : public AHUD {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Tss HUD | References")
	TSubclassOf<UTssPlayerOverlayWidget> overlayWidgetAsset;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tss HUD | References")
	TSubclassOf<UTssWidgetController> overlayWidgetControllerAsset; 
	
	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------

private: 
	
	UPROPERTY(Transient)
	TObjectPtr<UTssPlayerOverlayWidget> overlayWidget;
	
	UPROPERTY(Transient)
	TObjectPtr<UTssCharacterWidgetController> overlayWidgetController; 
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	void InitHud(TObjectPtr<UTssAbilitySystemComponent> asc, TObjectPtr<UTssAttributeSet> as, TObjectPtr<ATssCharacter> character); 
};
