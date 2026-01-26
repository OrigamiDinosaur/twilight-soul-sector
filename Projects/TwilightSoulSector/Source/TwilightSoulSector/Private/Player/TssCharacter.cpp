// Origami Dinosaur Creations 2026 (C)

#include "Player/TssCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

void ATssCharacter::BeginPlay() {
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed; 
}

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

void ATssCharacter::SetIsRunning(const bool isRunning) {
	GetCharacterMovement()->MaxWalkSpeed = isRunning ? runSpeed : walkSpeed; 
}
