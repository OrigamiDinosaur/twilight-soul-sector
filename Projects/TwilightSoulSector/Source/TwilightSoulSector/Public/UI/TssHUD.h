// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "TssCharacterWidgetController.h"
#include "TssPlayerMenuWidget.h"
#include "TssPlayerMenuWidgetController.h"
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
			
	UPROPERTY(EditDefaultsOnly, Category = "Tss HUD | References")
	TSubclassOf<UTssPlayerMenuWidget> playerMenuWidgetAsset;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tss HUD | References")
	TSubclassOf<UTssPlayerMenuWidgetController> playerMenuWidgetControllerAsset;
	
	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------

private: 
	
	UPROPERTY(Transient)
	TObjectPtr<UTssPlayerOverlayWidget> overlayWidget;
	
	UPROPERTY(Transient)
	TObjectPtr<UTssCharacterWidgetController> overlayWidgetController; 
	
	UPROPERTY(Transient)
	TObjectPtr<UTssPlayerMenuWidget> playerMenuWidget;
	
	UPROPERTY(Transient)
	TObjectPtr<UTssPlayerMenuWidgetController> playerMenuWidgetController; 
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	void InitHud(TObjectPtr<UTssAbilitySystemComponent> asc, TObjectPtr<UTssAttributeSet> as, TObjectPtr<ATssCharacter> character); 
	
	void ShowHidePlayerMenu(bool shouldShow);
};
