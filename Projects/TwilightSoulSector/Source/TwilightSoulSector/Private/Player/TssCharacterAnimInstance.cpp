// Origami Dinosaur Creations 2026 (C)

#include "Player/TssCharacterAnimInstance.h"

#include "Debug/DebugLog.h"

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

void UTssCharacterAnimInstance::SetLocomotion(const float horizontal, const float vertical) {
	
	const float mappedHorizontal = FMath::Lerp(0.0f, locoMaxInfluence, horizontal);
	const float mappedVertical = FMath::Lerp(0.0f, locoMaxInfluence, vertical); 
		
	locoHorizontalInfluence = mappedHorizontal; 
	locoVerticalInfluence = mappedVertical; 
	
}
