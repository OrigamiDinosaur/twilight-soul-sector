// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssAbilitySystemLibrary.h"

#include "GameplayTagContainer.h"
#include "Debug/DebugLog.h"

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

bool UTssAbilitySystemLibrary::GetGameplayTagFromName(FName inName, FGameplayTag& tag) {

	LOGPARAMS("Tag %s", *inName.ToString())
	
	tag = FGameplayTag::RequestGameplayTag(inName);
	return tag.IsValid();	
}
