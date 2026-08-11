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
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	virtual void BeginPlay() override;
	
};
