// Origami Dinosaur Creations 2026 (C)

#include "Player/TssCharacter.h"

#include "AbilitySystem/ExperienceCalculator.h"
#include "AbilitySystem/TssGameplayTags.h"
#include "Components/CapsuleComponent.h"
#include "Debug/DebugLog.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------


void ATssCharacter::BeginPlay() {
	Super::BeginPlay();
		
	animInstance = Cast<UTssCharacterAnimInstance>(GetMesh()->GetAnimInstance()); 
	
	if (!animInstance) {
		LOGERROR("Anim Instance not found in TssCharacter"); 
	}
	
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;

	equippedPrimaryAbilityTag = defaultPrimaryAbilityTag; 
	equippedSecondaryAbilityTag = defaultSecondaryAbilityTag; 
	
	for (const TObjectPtr<UTssAbilityInfo>& info : startingAbilities) {
		EquipAbility(info); 
	}
	
	if (ExpUpdated.IsBound()) ExpUpdated.Broadcast(0.0f); 
	if (LevelUpdated.IsBound()) LevelUpdated.Broadcast(characterLevel); 
	if (AttributePointsUpdated.IsBound()) AttributePointsUpdated.Broadcast(0); 
}

void ATssCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

void ATssCharacter::SetIsRunning(const bool inIsRunning) {
	GetCharacterMovement()->MaxWalkSpeed = inIsRunning ? runSpeed : walkSpeed; 
	isRunning = inIsRunning; 
}

void ATssCharacter::PrimaryPressed() const {
	abilitySystemComponent->AbilityPressed(equippedPrimaryAbilityTag);
}

void ATssCharacter::PrimaryHeld() const {
	abilitySystemComponent->AbilityHeld(equippedPrimaryAbilityTag); 
}

void ATssCharacter::PrimaryReleased() const {
	abilitySystemComponent->AbilityReleased(equippedPrimaryAbilityTag); 
}

void ATssCharacter::SecondaryPressed() const {
	abilitySystemComponent->AbilityPressed(equippedSecondaryAbilityTag);
}

void ATssCharacter::SecondaryHeld() const {
	abilitySystemComponent->AbilityHeld(equippedSecondaryAbilityTag); 
}

void ATssCharacter::SecondaryReleased() const {
	abilitySystemComponent->AbilityReleased(equippedSecondaryAbilityTag); 
}

void ATssCharacter::FaceTarget(const FVector& facingTarget) {
	if (isDead) return; 
	
	const FVector actorLocation = GetActorLocation();
	FVector adjustedFacingTarget = facingTarget; 
	adjustedFacingTarget.Z = actorLocation.Z;

	const FVector facingDirection = adjustedFacingTarget - actorLocation; 
	SetActorRotation(facingDirection.Rotation()); 
	
	UpdateLocomotionAnimation(); 
}

void ATssCharacter::AllowAbilityEquip(const TObjectPtr<UTssAbilityInfo> ability) {
	equippableAbility = ability;	
	abilitySystemComponent->AddLooseGameplayTag(FTssGameplayTags::Get().State_Player_Equip); 
	if (AbilityEquipAvailable.IsBound()) AbilityEquipAvailable.Broadcast();
}

void ATssCharacter::DisableAbilityEquip() {
	equippableAbility = nullptr; 	
	abilitySystemComponent->RemoveLooseGameplayTag(FTssGameplayTags::Get().State_Player_Equip); 
	if (AbilityEquipUnavailable.IsBound()) AbilityEquipUnavailable.Broadcast(); 
}

void ATssCharacter::AttemptEquipPrimary() {
	if (equippableAbility == nullptr || equippableAbility->abilityTag == equippedPrimaryAbilityTag || !abilitySystemComponent->HasMatchingGameplayTag(FTssGameplayTags::Get().State_Player_Equip)) return; 
			
	if (equipSfx) UGameplayStatics::PlaySound2D(this, equipSfx); 
	
	abilitySystemComponent->RemoveCharacterAbility(equippedPrimaryAbilityTag); 
	
	equippedPrimaryAbilityTag = equippableAbility->abilityTag; 	
	
	if (equippedPrimaryAbilityTag == equippedSecondaryAbilityTag) {
				
		abilitySystemComponent->RemoveCharacterAbility(equippedSecondaryAbilityTag); 
		if (SecondaryAbilityUnassigned.IsBound()) SecondaryAbilityUnassigned.Broadcast(); 
		equippedSecondaryAbilityTag = FGameplayTag(); 
	}
	
	EquipAbility(equippableAbility); 
}

void ATssCharacter::AttemptEquipSecondary() {
	if (equippableAbility == nullptr || equippableAbility->abilityTag == equippedSecondaryAbilityTag || !abilitySystemComponent->HasMatchingGameplayTag(FTssGameplayTags::Get().State_Player_Equip)) return; 
		
	if (equipSfx) UGameplayStatics::PlaySound2D(this, equipSfx); 
	
	abilitySystemComponent->RemoveCharacterAbility(equippedSecondaryAbilityTag); 
	
	equippedSecondaryAbilityTag = equippableAbility->abilityTag; 	
	
	if (equippedPrimaryAbilityTag == equippedSecondaryAbilityTag) {
		abilitySystemComponent->RemoveCharacterAbility(equippedPrimaryAbilityTag); 
		if (PrimaryAbilityUnassigned.IsBound()) PrimaryAbilityUnassigned.Broadcast(); 
		equippedPrimaryAbilityTag = FGameplayTag(); 
	}
	
	EquipAbility(equippableAbility); 
}

void ATssCharacter::Collect(const FGameplayTag collectionTag, const int magnitude) {	
	
	if (collectionTag == FTssGameplayTags::Get().Collectable_Exp) {
		AddExp(magnitude);
	}
}

void ATssCharacter::UpgradeAttribute(FGameplayTag attributeTag) {
	if (numAttributePoints <= 0) return; 
	
	numAttributePoints--; 
	
	if (AttributePointsUpdated.IsBound()) AttributePointsUpdated.Broadcast(numAttributePoints); 
	
	TArray<FTaggedMagnitude> taggedMagnitudes; 
	
	for (FGameplayTag tag : attributeTags) {

		const float attributeValue = tag.MatchesTagExact(attributeTag) ? 1 : 0; 
		
		taggedMagnitudes.Add(FTaggedMagnitude(tag, attributeValue)); 
	}
	
	abilitySystemComponent->ApplyMagnitudesByCallerEffect(attributeChangeEffect, taggedMagnitudes); 
}

//-----------------------------------------------------------------------------------------
// Protected Methods:
//-----------------------------------------------------------------------------------------	
	
FVector ATssCharacter::GetSocketByIndex_Implementation(const int socketIndex) {	
	return GetMesh()->GetSocketLocation(sockets[socketIndex]); 
}

void ATssCharacter::HandleDeath_Implementation() {
	Super::HandleDeath_Implementation();
	
	isDead = true; 
	
	if (animInstance) animInstance->SetShouldDie(true); 
		
	SetActorEnableCollision(false); 
}

//-----------------------------------------------------------------------------------------
// Private Methods:
//-----------------------------------------------------------------------------------------	

void ATssCharacter::EquipAbility(const TObjectPtr<UTssAbilityInfo>& abilityInfo) {

	const FTssGameplayTags tags = FTssGameplayTags::Get();

	FGameplayTag montageTag = abilityInfo->montageTag; 
	
	// check if our tag is our arms tag. If so reassign to the sub tag arms primary or secondary based on where its equipped. 
	if (montageTag == tags.Montage_Arms) {
		
		if (abilityInfo->abilityTag == equippedPrimaryAbilityTag) {
			montageTag = tags.Montage_Arms_Primary;
		}
		else if (abilityInfo->abilityTag == equippedSecondaryAbilityTag) {
			montageTag = tags.Montage_Arms_Secondary; 
		}
	}
	
	if (abilityInfo->abilityTag == equippedPrimaryAbilityTag) {
		if (PrimaryAbilityAssigned.IsBound()) PrimaryAbilityAssigned.Broadcast(abilityInfo); 
	}
	
	if (abilityInfo->abilityTag == equippedSecondaryAbilityTag) {
		if (SecondaryAbilityAssigned.IsBound()) SecondaryAbilityAssigned.Broadcast(abilityInfo); 
	}
	
	abilitySystemComponent->AddCharacterAbility(abilityInfo->ability, montageTag); 
}

void ATssCharacter::UpdateLocomotionAnimation() {
	
	const float currentSpeed = GetMovementComponent()->Velocity.Length(); 
	
	if (currentSpeed <= 1.0f) {
		animInstance->SetShouldMove(false); 
		return; 
	}
	
	animInstance->SetShouldMove(true); 
	
	const FVector facingDirection = GetActorForwardVector();
	const FVector leftDirection = GetActorRightVector(); 
	FVector movementDirection = GetMovementComponent()->Velocity; 
	movementDirection.Normalize();

	const float similarityToForward = facingDirection.Dot(movementDirection);
	const float rawVertical = (similarityToForward + 1.0f) / 2.0f; 
	
	float adjustedVertical = rawVertical; 
	
	if (!isRunning) {
		adjustedVertical = FMath::Lerp(0.25f, 0.75f, rawVertical); 
	}
	
	const float similarityToLeft = leftDirection.Dot(movementDirection); 
	const float rawHorizontal = (similarityToLeft + 1.0f) / 2.0f; 
	
	float adjustedHorizonal = rawHorizontal; 
	
	if (!isRunning) {
		adjustedHorizonal = FMath::Lerp(0.25f, 0.75f, rawHorizontal); 
	}
	
	animInstance->SetLocomotion(adjustedHorizonal, adjustedVertical); 	
}

void ATssCharacter::AddExp(const int expAmount) {

	// todo: its technically possible we could get enough exp to level up twice and this doesn't handle this
	// todo: figure out a better solution. 
	
	// cache our exp calculator.
	const UExperienceCalculator* calculator = GetWorld()->GetSubsystem<UExperienceCalculator>();
	
	// get our exp threshold for our next level. 
	int expThreshold = calculator->GetThresholdForLevel(characterLevel + 1); 
	
	// add our exp and see if we've levelled up. 
	expTotal += expAmount; 
		
	if (expTotal >= expThreshold) {		
		LevelUp();
	}	
	
	// get our exp bar limits for calculating our progress bar. 
	// we re-grab the exp threshold as we m,ay have levelled. 
	const int previousExpThreshold = calculator->GetThresholdForLevel(characterLevel); 
	expThreshold = calculator->GetThresholdForLevel(characterLevel + 1);

	const float normalizedExperience = UKismetMathLibrary::NormalizeToRange(expTotal, previousExpThreshold, expThreshold);

	// tell the gui to update our progress bar. 
	if (ExpUpdated.IsBound()) ExpUpdated.Broadcast(normalizedExperience);
}

void ATssCharacter::LevelUp() {
	
	// increase our level, and update our exp calculator and gui. 
	characterLevel++; 	
	GetWorld()->GetSubsystem<UExperienceCalculator>()->SetPlayerLevel(characterLevel); 
	
	if (LevelUpdated.IsBound()) LevelUpdated.Broadcast(characterLevel); 
		
	if (levelUpSfx) UGameplayStatics::PlaySound2D(this, levelUpSfx); 
	
	// increase our number of attribute points and tell our gui.
	numAttributePoints++; 
	
	if (AttributePointsUpdated.IsBound()) AttributePointsUpdated.Broadcast(numAttributePoints); 	
}

