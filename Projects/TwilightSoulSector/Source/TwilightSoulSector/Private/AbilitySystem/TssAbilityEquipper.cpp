// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssAbilityEquipper.h"

#include "Player/TssCharacter.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

ATssAbilityEquipper::ATssAbilityEquipper() {
	PrimaryActorTick.bCanEverTick = true;
}

void ATssAbilityEquipper::BeginPlay() {
	Super::BeginPlay();
}

void ATssAbilityEquipper::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

//-----------------------------------------------------------------------------------------
// Protected Methods:
//-----------------------------------------------------------------------------------------

void ATssAbilityEquipper::AttemptAllowCharacterEquip(AActor* actor) {
	
	if (ATssCharacter* character = Cast<ATssCharacter>(actor)) {
		character->AllowAbilityEquip(abilityToEquip); 
	}
}

void ATssAbilityEquipper::AttemptDisableCharacterEquip(AActor* actor) {
	
	if (ATssCharacter* character = Cast<ATssCharacter>(actor)) {
		character->DisableAbilityEquip(); 
	}
}
