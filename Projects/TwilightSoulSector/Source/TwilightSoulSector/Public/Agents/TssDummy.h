// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "TssDummyAnimInstance.h"
#include "TssEnemyBase.h"
#include "TssDummy.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API ATssDummy : public ATssEnemyBase {
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
