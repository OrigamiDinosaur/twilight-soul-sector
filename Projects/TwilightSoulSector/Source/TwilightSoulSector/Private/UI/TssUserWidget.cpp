// Origami Dinosaur Creations 2026 (C)

#include "UI/TssUserWidget.h"

//-----------------------------------------------------------------------------------------
// Getters / Setters:
//-----------------------------------------------------------------------------------------

void UTssUserWidget::SetWidgetController(UTssWidgetController* inWidgetController) {
	
	widgetController = inWidgetController; 
	WidgetControllerSet_BP();
}
