// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "Player/TssCharacterBase.h"
#include "TssCharacter.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API ATssCharacter : public ATssCharacterBase {
	GENERATED_BODY()

	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Character | Movement")
	float walkSpeed; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Character | Movement")
	float runSpeed; 
	
	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------

protected:
	
	virtual void BeginPlay() override;
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------

public: 
	
	void SetIsRunning(bool isRunning);
};
