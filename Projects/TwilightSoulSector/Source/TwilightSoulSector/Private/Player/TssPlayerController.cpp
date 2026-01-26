// Origami Dinosaur Creations 2026 (C)

#include "Player/TssPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

void ATssPlayerController::BeginPlay() {
	Super::BeginPlay();

	// cursor setup
	bShowMouseCursor = true;

	// base input setup
	FInputModeGameAndUI inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(inputModeData);

	// check for our context.
	if (!inputContext) {
		UE_LOG(LogTemp, Error, TEXT("Input Context not found in TssPlayerController!"));
	}
	else {

		// assign our context. 
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
			subsystem->AddMappingContext(inputContext, 0);
		}			
	}
}

void ATssPlayerController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	
	tssCaracter = Cast<ATssCharacter>(InPawn); 
	
	if (!tssCaracter) {
		UE_LOG(LogTemp, Error, TEXT("Character Not Properly Cast in TssPlayerController!"));
	}
}

void ATssPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(InputComponent); 
	
	input->BindAction(moveAction, ETriggerEvent::Triggered, this, &ATssPlayerController::Input_Move); 
	input->BindAction(shiftAction, ETriggerEvent::Started, this, &ATssPlayerController::Input_ShiftPressed); 
	input->BindAction(shiftAction, ETriggerEvent::Completed, this, &ATssPlayerController::Input_ShiftReleased); 
}

//-----------------------------------------------------------------------------------------
// Event Handlers:
//-----------------------------------------------------------------------------------------

void ATssPlayerController::Input_Move(const FInputActionValue& inputActionValue) {
	
	const FVector2D inputAxisVector = inputActionValue.Get<FVector2D>();
	const FRotator rotation = GetControlRotation();
	const FRotator yawRotation(0.0f, rotation.Yaw, 0.0f);

	// get our vectors. 
	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	if (tssCaracter) {

		tssCaracter->AddMovementInput(forwardDirection, inputAxisVector.Y);
		tssCaracter->AddMovementInput(rightDirection, inputAxisVector.X); 
	}	
}

void ATssPlayerController::Input_ShiftPressed() {
	
	if (tssCaracter) tssCaracter->SetIsRunning(true); 
}

void ATssPlayerController::Input_ShiftReleased() {
	
	if (tssCaracter) tssCaracter->SetIsRunning(false); 
}
