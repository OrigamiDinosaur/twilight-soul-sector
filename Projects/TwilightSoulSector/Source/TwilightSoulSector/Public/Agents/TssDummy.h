// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "TssDummyAnimInstance.h"
#include "Player/TssCharacterBase.h"
#include "TssDummy.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API ATssDummy : public ATssCharacterBase {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------
	
private:
	
	UPROPERTY(Transient)
	TObjectPtr<UTssDummyAnimInstance> animInstance;
	
	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	virtual void BeginPlay() override;
	
	//-----------------------------------------------------------------------------------------
	// Protected Methods:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	virtual void HandleDeath_Implementation() override;
};
