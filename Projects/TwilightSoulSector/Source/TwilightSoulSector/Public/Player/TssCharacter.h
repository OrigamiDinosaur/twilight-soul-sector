// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "TssCharacterAnimInstance.h"
#include "AbilitySystem/TssAbilityInfo.h"
#include "Components/WidgetComponent.h"
#include "Player/TssCharacterBase.h"
#include "UI/TssUserWidget.h"
#include "TssCharacter.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API ATssCharacter : public ATssCharacterBase {
	GENERATED_BODY()

	//-----------------------------------------------------------------------------------------
	// Components:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Tss Character | Components")
	TObjectPtr<UWidgetComponent> vitalAttributesWidgetComponent; 
	
	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Tss Character | References")
	TSubclassOf<UTssWidgetController> widgetControllerAsset;	
	
	UPROPERTY(EditDefaultsOnly, Category = "Tss Character | Defaults")
	TArray<TObjectPtr<UTssAbilityInfo>> startingAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tss Character | Defaults")
	FGameplayTag defaultPrimaryAbilityTag;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tss Character | Defaults")
	FGameplayTag defaultSecondaryAbilityTag;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tss Character | Movement")
	float walkSpeed; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Tss Character | Movement")
	float runSpeed; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Tss Character | Sockets")
	TArray<FName> sockets; 
	
	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------
	
private:
	
	UPROPERTY(Transient)
	TObjectPtr<UTssUserWidget> vitalAttributesWidget;
	
	UPROPERTY(Transient)
	TObjectPtr<UTssWidgetController> widgetController;
	
	UPROPERTY(Transient)
	TObjectPtr<UTssCharacterAnimInstance> animInstance; 
	
	UPROPERTY(Transient)
	TObjectPtr<UTssAbilityInfo> equippableAbility; 
	
	FRotator startingWorldRotation; 

	FGameplayTag equippedPrimaryAbilityTag; 
	FGameplayTag equippedSecondaryAbilityTag; 

	bool isRunning;
	
	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------

public: 
		
	ATssCharacter();
	
protected:
	
	virtual void BeginPlay() override;
	
public: 
	
	virtual void Tick(float DeltaSeconds) override;
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------

public: 
		
	void SetIsRunning(bool inIsRunning);
	
	void PrimaryPressed() const; 
	void PrimaryHeld() const; 
	void PrimaryReleased() const; 
	
	void SecondaryPressed() const; 
	void SecondaryHeld() const; 
	void SecondaryReleased() const; 
	
	void FaceTarget(const FVector& facingTarget); 
	
	void AllowAbilityEquip(TObjectPtr<UTssAbilityInfo> ability);
	void DisableAbilityEquip(); 
	
	void AttemptEquipPrimary();
	void AttemptEquipSecondary(); 
	
	//-----------------------------------------------------------------------------------------
	// Protected Methods:
	//-----------------------------------------------------------------------------------------	
	
protected:
	
	virtual FVector GetSocketByIndex_Implementation(int socketIndex) override; 
	virtual void HandleDeath_Implementation() override;
	
	//-----------------------------------------------------------------------------------------
	// Private Methods:
	//-----------------------------------------------------------------------------------------	
	
private:
	
	void EquipAbility(const TObjectPtr<UTssAbilityInfo>& abilityInfo); 
	void UpdateLocomotionAnimation(); 
};
