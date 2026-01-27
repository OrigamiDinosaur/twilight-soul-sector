// Origami Dinosaur Creations 2026 (C)

#include "Player/TssCharacterBase.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

ATssCharacterBase::ATssCharacterBase() {
	PrimaryActorTick.bCanEverTick = true;
	
	abilitySystemComponent = CreateDefaultSubobject<UTssAbilitySystemComponent>("AbilitySystemComponent");
	attributeSet = CreateDefaultSubobject<UTssAttributeSet>("Attribute Set");
}

void ATssCharacterBase::BeginPlay() {
	Super::BeginPlay();
}

void ATssCharacterBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}