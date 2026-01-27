// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TssAssetManager.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssAssetManager : public UAssetManager {
	GENERATED_BODY()
		
	//-----------------------------------------------------------------------------------------
	// Getters / Setters:
	//-----------------------------------------------------------------------------------------

public: 
	
	static UTssAssetManager& Get(); 
	
	//-----------------------------------------------------------------------------------------
	// Protected Methods:
	//-----------------------------------------------------------------------------------------

protected:

	virtual void StartInitialLoading() override;

};
