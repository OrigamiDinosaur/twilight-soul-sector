// Origami Dinosaur Creations 2026 (C)

#include "Player/TssCharacter.h"

#include "AbilitySystem/TssGameplayTags.h"
#include "Components/CapsuleComponent.h"
#include "Debug/DebugLog.h"
#include "GameFramework/CharacterMovementComponent.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

ATssCharacter::ATssCharacter() {
	
	vitalAttributesWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Vital Attributes Widget");
	vitalAttributesWidgetComponent->SetupAttachment(RootComponent);
}

void ATssCharacter::BeginPlay() {
	Super::BeginPlay();
	
	// get our widget from our widget component.
	vitalAttributesWidget = Cast<UTssUserWidget>(vitalAttributesWidgetComponent->GetWidget()); 
	
	if (!vitalAttributesWidget) {
		LOGERROR("VitalAttributesWidget not retrieved in TssCharacter"); 
	}
	else {
				
		// create our widget controller and assign it to our widget.
		if (!widgetControllerAsset) {
			LOGERROR("WidgetControllerAsset not assigned in TssCharacter")
		}
		else {
			
			widgetController = NewObject<UTssWidgetController>(this, widgetControllerAsset); 		
			widgetController->SetAbilitySystemComponent(abilitySystemComponent);
			widgetController->SetAttributeSet(attributeSet); 
			widgetController->BindCallbacksToDependencies();
									
			vitalAttributesWidget->SetWidgetController(widgetController); 			
			widgetController->BroadcastInitialValues();
		}		
	}
	
	animInstance = Cast<UTssCharacterAnimInstance>(GetMesh()->GetAnimInstance()); 
	
	if (!animInstance) {
		LOGERROR("Anim Instance not found in TssCharacter"); 
	}
	
	startingWorldRotation = vitalAttributesWidgetComponent->GetComponentRotation();	
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;

	equippedPrimaryAbilityTag = defaultPrimaryAbilityTag; 
	equippedSecondaryAbilityTag = defaultSecondaryAbilityTag; 
	
	for (const TObjectPtr<UTssAbilityInfo>& info : startingAbilities) {
		EquipAbility(info); 
	}
}

void ATssCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	
	vitalAttributesWidgetComponent->SetWorldRotation(startingWorldRotation);
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
}

void ATssCharacter::DisableAbilityEquip() {
	
	equippableAbility = nullptr; 	
	abilitySystemComponent->RemoveLooseGameplayTag(FTssGameplayTags::Get().State_Player_Equip); 
}

void ATssCharacter::AttemptEquipPrimary() {
	if (equippableAbility == nullptr || equippableAbility->abilityTag == equippedPrimaryAbilityTag || !abilitySystemComponent->HasMatchingGameplayTag(FTssGameplayTags::Get().State_Player_Equip)) return; 
	
	abilitySystemComponent->RemoveCharacterAbility(equippedPrimaryAbilityTag); 
	
	equippedPrimaryAbilityTag = equippableAbility->abilityTag; 	
	
	if (equippedPrimaryAbilityTag == equippedSecondaryAbilityTag) {
		abilitySystemComponent->RemoveCharacterAbility(equippedSecondaryAbilityTag); 
		equippedSecondaryAbilityTag = FGameplayTag(); 
	}
	
	EquipAbility(equippableAbility); 
}

void ATssCharacter::AttemptEquipSecondary() {
	if (equippableAbility == nullptr || equippableAbility->abilityTag == equippedSecondaryAbilityTag || !abilitySystemComponent->HasMatchingGameplayTag(FTssGameplayTags::Get().State_Player_Equip)) return; 
	
	abilitySystemComponent->RemoveCharacterAbility(equippedSecondaryAbilityTag); 
	
	equippedSecondaryAbilityTag = equippableAbility->abilityTag; 	
	
	if (equippedPrimaryAbilityTag == equippedSecondaryAbilityTag) {
		abilitySystemComponent->RemoveCharacterAbility(equippedPrimaryAbilityTag); 
		equippedPrimaryAbilityTag = FGameplayTag(); 
	}
	
	EquipAbility(equippableAbility); 
}

//-----------------------------------------------------------------------------------------
// Protected Methods:
//-----------------------------------------------------------------------------------------	
	
FVector ATssCharacter::GetSocketByIndex_Implementation(const int socketIndex) {	
	return GetMesh()->GetSocketLocation(sockets[socketIndex]); 
}

void ATssCharacter::HandleDeath_Implementation() {
	Super::HandleDeath_Implementation();
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

