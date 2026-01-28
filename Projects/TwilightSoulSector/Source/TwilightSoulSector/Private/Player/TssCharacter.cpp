// Origami Dinosaur Creations 2026 (C)

#include "Player/TssCharacter.h"

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

void ATssCharacter::SetIsRunning(const bool isRunning) const {
	GetCharacterMovement()->MaxWalkSpeed = isRunning ? runSpeed : walkSpeed; 
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

FVector ATssCharacter::GetSocketByIndex_Implementation(const int socketIndex) {	
	return GetMesh()->GetSocketLocation(sockets[socketIndex]); 
}
