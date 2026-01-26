// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "TssCharacter.h"
#include "TssPlayerController.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API ATssPlayerController : public APlayerController {

	GENERATED_BODY()

	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Player Controller | References")
	TObjectPtr<UInputMappingContext> inputContext;

	UPROPERTY(EditDefaultsOnly, Category = "Player Controller | References")
	TObjectPtr<UInputAction> moveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Player Controller | References")
	TObjectPtr<UInputAction> shiftAction;

	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------

private:

	UPROPERTY(Transient)
	TObjectPtr<ATssCharacter> tssCaracter; 
	
	bool isShiftKeyDown;

	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------

protected:

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

	//-----------------------------------------------------------------------------------------
	// Event Handlers:
	//-----------------------------------------------------------------------------------------

private:

	void Input_Move(const FInputActionValue& inputActionValue);
	void Input_ShiftPressed();
	void Input_ShiftReleased(); 
};
