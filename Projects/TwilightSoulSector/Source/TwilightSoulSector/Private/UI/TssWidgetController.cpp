// Origami Dinosaur Creations 2026 (C)

#include "UI/TssWidgetController.h"

#include "Debug/DebugLog.h"

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

void UTssWidgetController::BroadcastInitialValues() {
	if (!abilitySystemComponent || !attributeSet) {
		LOGERROR("Asc or As not assigned in TssWidgetController");
		return; 
	}
	
	TArray<FGameplayTag> listenTags;
	tagsToListenFor.GetGameplayTagArray(listenTags);

	for (FGameplayTag& listenTag : listenTags) {
		
		FGameplayAttribute attributeToListenTo = attributeSet->GetAttributeFromTag(listenTag);
		const float attributeValue = attributeToListenTo.GetNumericValue(attributeSet);		
				
		if (AttributeChangedDelegate.IsBound()) AttributeChangedDelegate.Broadcast(listenTag, attributeValue); 
	}
}

void UTssWidgetController::BindCallbacksToDependencies() {
	if (!abilitySystemComponent || !attributeSet) {
		LOGERROR("Asc or As not assigned in TssWidgetController");
		return; 
	}
	
	TArray<FGameplayTag> listenTags;
	tagsToListenFor.GetGameplayTagArray(listenTags);

	for (FGameplayTag& listenTag : listenTags) {

		const FGameplayAttribute attributeToListenTo = attributeSet->GetAttributeFromTag(listenTag); 
		
		abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(attributeToListenTo).AddLambda(
			[this, listenTag](const FOnAttributeChangeData& data) {
				BroadcastAttributeChange(listenTag); 
		});
	}
}

void UTssWidgetController::BroadcastAttributeChange(const FGameplayTag attributeTag) {

	const FGameplayAttribute attribute = attributeSet->GetAttributeFromTag(attributeTag); 		
	if (AttributeChangedDelegate.IsBound()) AttributeChangedDelegate.Broadcast(attributeTag, attribute.GetNumericValue(attributeSet)); 
}
