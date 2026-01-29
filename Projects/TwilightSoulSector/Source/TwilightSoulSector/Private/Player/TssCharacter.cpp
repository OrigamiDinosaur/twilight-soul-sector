// Origami Dinosaur Creations 2026 (C)

#include "Player/TssCharacter.h"

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
	abilitySystemComponent->AbilityPressed(primaryAbilityTag);
}

void ATssCharacter::PrimaryHeld() const {
	abilitySystemComponent->AbilityHeld(primaryAbilityTag); 
}

void ATssCharacter::PrimaryReleased() const {
	abilitySystemComponent->AbilityReleased(primaryAbilityTag); 
}

void ATssCharacter::FaceTarget(const FVector& facingTarget) {

	const FVector actorLocation = GetActorLocation();
	FVector adjustedFacingTarget = facingTarget; 
	adjustedFacingTarget.Z = actorLocation.Z;

	const FVector facingDirection = adjustedFacingTarget - actorLocation; 
	SetActorRotation(facingDirection.Rotation()); 
	
	UpdateLocomotionAnimation(); 
}

//-----------------------------------------------------------------------------------------
// Protected Methods:
//-----------------------------------------------------------------------------------------	
	
FVector ATssCharacter::GetSocketByIndex_Implementation(const int socketIndex) {	
	return GetMesh()->GetSocketLocation(sockets[socketIndex]); 
}

//-----------------------------------------------------------------------------------------
// Private Methods:
//-----------------------------------------------------------------------------------------	

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

