// Origami Dinosaur Creations 2026 (C)


#include "Agents/TssDummy.h"

#include "Debug/DebugLog.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

void ATssDummy::BeginPlay() {
	Super::BeginPlay();
	
	animInstance = Cast<UTssDummyAnimInstance>(GetMesh()->GetAnimInstance()); 
	
	if (!animInstance) {
		LOGERROR("AnimInstance not found in TssDummy");
	}
}

//-----------------------------------------------------------------------------------------
// Protected Methods:
//-----------------------------------------------------------------------------------------

void ATssDummy::HandleDeath_Implementation() {	
	if (animInstance) animInstance->SetShouldDie(true); 
	
	SetActorEnableCollision(false); 
}
