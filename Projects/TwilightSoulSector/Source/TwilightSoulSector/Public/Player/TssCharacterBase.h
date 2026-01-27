// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/TssAbilitySystemComponent.h"
#include "AbilitySystem/TssAttributeSet.h"
#include "GameFramework/Character.h"
#include "TssCharacterBase.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API ATssCharacterBase : public ACharacter {
	GENERATED_BODY()

	//-----------------------------------------------------------------------------------------
	// Components:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	// making this as a single player local game, so going to allow the characters to have their 
	// own asc and attribute sets. may move these into the player state later if need be.
	UPROPERTY(EditDefaultsOnly, Category = "Tss Character Base | Components")
	TObjectPtr<UTssAbilitySystemComponent> abilitySystemComponent;  
	
	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------
	
private:
	
	UPROPERTY(Transient)
	TObjectPtr<UTssAttributeSet> attributeSet;
	
	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------

public:

	ATssCharacterBase();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

};
