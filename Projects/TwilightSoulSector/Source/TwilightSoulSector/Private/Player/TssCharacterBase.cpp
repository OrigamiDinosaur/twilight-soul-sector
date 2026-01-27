// Origami Dinosaur Creations 2026 (C)

#include "Player/TssCharacterBase.h"

#include "Debug/DebugLog.h"

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
	
	if (!attributeSet) {
		LOGERROR("Attribute Set not found in TssCharacterBase"); 
	}
	else {
				
		abilitySystemComponent->InitStats(UTssAttributeSet::StaticClass(), defaultAttribues); 
		
		attributeSet->FullRestore(); 
	}
}

void ATssCharacterBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}