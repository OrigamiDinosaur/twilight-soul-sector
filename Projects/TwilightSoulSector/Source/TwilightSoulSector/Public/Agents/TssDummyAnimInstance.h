// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TssDummyAnimInstance.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssDummyAnimInstance : public UAnimInstance {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	bool shouldDie; 
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	void SetShouldDie(const bool inShouldDie) { shouldDie = inShouldDie; }
};
