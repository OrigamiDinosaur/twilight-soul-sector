// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssAbilitySystemLibrary.h"

#include "GameplayTagContainer.h"

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

bool UTssAbilitySystemLibrary::GetGameplayTagFromName(FName inName, FGameplayTag& tag) {

	tag = FGameplayTag::RequestGameplayTag(inName);
	return tag.IsValid();	
}
