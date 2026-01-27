// Origami Dinosaur Creations 2026 (C)

#include "TssAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "AbilitySystem/TssGameplayTags.h"
#include "Debug/DebugLog.h"

//-----------------------------------------------------------------------------------------
// Getters / Setters:
//-----------------------------------------------------------------------------------------

UTssAssetManager& UTssAssetManager::Get() {
	
	if (!GEngine) {
		LOGERROR("GEngine not found in AssetManager");		
	}
	
	UTssAssetManager* tssAssetManager = Cast<UTssAssetManager>(GEngine->AssetManager); 
	return *tssAssetManager;	
}

//-----------------------------------------------------------------------------------------
// Protected Methods:
//-----------------------------------------------------------------------------------------

void UTssAssetManager::StartInitialLoading() {
	Super::StartInitialLoading();
	
	FTssGameplayTags::InitializeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData(); 
}
