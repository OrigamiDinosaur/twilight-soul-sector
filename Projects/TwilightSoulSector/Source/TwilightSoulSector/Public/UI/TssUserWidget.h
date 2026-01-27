// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "TssWidgetController.h"
#include "Blueprint/UserWidget.h"
#include "TssUserWidget.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssUserWidget : public UUserWidget {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Protected Fields:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UPROPERTY(BlueprintReadOnly, Category = "Tss Widget")
	TObjectPtr<UTssWidgetController> widgetController; 
	
	//-----------------------------------------------------------------------------------------
	// Getters / Setters:
	//-----------------------------------------------------------------------------------------
	
public:
	
	void SetWidgetController(UTssWidgetController* inWidgetController);
	
	//-----------------------------------------------------------------------------------------
	// Blueprint Implementable Events:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Tss Widget")
	void WidgetControllerSet_BP(); 
};
