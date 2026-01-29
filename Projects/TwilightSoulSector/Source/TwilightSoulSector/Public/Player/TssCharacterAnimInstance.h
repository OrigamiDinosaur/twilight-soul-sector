// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TssCharacterAnimInstance.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssCharacterAnimInstance : public UAnimInstance {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim | Locomotion")
	bool shouldMove; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim | Locomotion")
	float locoHorizontalInfluence; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim | Locomotion")
	float locoVerticalInfluence;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim | Locomotion")
	float locoMaxInfluence = 100.0f;
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	void SetShouldMove(const bool inShouldMove) { shouldMove = inShouldMove; }
	void SetLocomotion(float horizontal, float vertical); 
};
