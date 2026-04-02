// Origami Dinosaur Creations 2026 (C)

#include "Player/TssCharacterBase.h"

#include "AbilitySystem/ExperienceCalculator.h"
#include "Components/CapsuleComponent.h"
#include "Debug/DebugLog.h"
#include "Kismet/KismetSystemLibrary.h"

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
		abilitySystemComponent->AddCharacterAbilities(defaultAbilities);
				
		if (IsValid(derivedAttributeCalculator)) ApplyEffectToSelf(derivedAttributeCalculator); 
		
		attributeSet->FullRestore(); 
		
		if (AttributesAssigned.IsBound()) AttributesAssigned.Broadcast(); 
	}
}

void ATssCharacterBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

void ATssCharacterBase::Die() {
	if (isDead) return; 
	
	isDead = true;
	
	HandleDeath();
}

//-----------------------------------------------------------------------------------------
// Protected Methods:
//-----------------------------------------------------------------------------------------

FVector ATssCharacterBase::GetSocketByIndex_Implementation(int socketIndex) {
	return FVector(); 
}

FTaggedMontage ATssCharacterBase::GetAbilityMontageByTag(const FGameplayTag& montageTag) {

	for (FTaggedMontage montage : abilityMontages) {
		if (montage.montageTag == montageTag) return montage;
	}

	return FTaggedMontage(); 
}

FVector ATssCharacterBase::GetFacingDirection() {
	return GetCapsuleComponent()->GetForwardVector();
}

void ATssCharacterBase::HandleDeath_Implementation() {
	SpawnExp();
}

void ATssCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect> gameplayEffectClass, const float level) {
	
	if (!IsValid(abilitySystemComponent)) {
		LOGERROR("Attempting to apply effect with invalid AbilitySystemComponent in TssCharacterBase"); 
		return; 
	}
	
	FGameplayEffectContextHandle effectContextHandle = abilitySystemComponent->MakeEffectContext();
	effectContextHandle.AddSourceObject(this); 
	
	const FGameplayEffectSpecHandle specHandle = abilitySystemComponent->MakeOutgoingSpec(gameplayEffectClass, level, effectContextHandle);
	abilitySystemComponent->ApplyGameplayEffectSpecToSelf(*specHandle.Data.Get()); 
}

//-----------------------------------------------------------------------------------------
// Private Methods:
//-----------------------------------------------------------------------------------------

void ATssCharacterBase::SpawnExp() {
	
	UWorld* world = GetWorld();
	const float degreesPerTurn = 360.0f / numExpShardsToDrop;

	const int totalExp = world->GetSubsystem<UExperienceCalculator>()->GetExpReward(characterLevel);
	const int expPerDrop = totalExp / numExpShardsToDrop; 
		
	for (int i = 0; i < numExpShardsToDrop; i++) {
		
		const float spawnDistance = FMath::RandRange(spawnDistanceMin, spawnDistanceMax);
		FVector forwardVector = GetActorForwardVector() * spawnDistance; 
		
		FVector rotatedForwardVector = forwardVector.RotateAngleAxis(degreesPerTurn * i, FVector::UpVector);
		
		FVector spawnLocation = GetMesh()->GetComponentLocation() + rotatedForwardVector;
		FRotator spawnRotation = FRotator(0.0f); 
		
		ACollectable* expDrop = world->SpawnActor<ACollectable>(expDropAsset, spawnLocation, spawnRotation); 
		expDrop->SetMagnitude(expPerDrop); 
		expDrop->SpawnCollectable();		
	}
}