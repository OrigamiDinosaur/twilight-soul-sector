// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Structs.h"
#include "AbilitySystem/TssAbilitySystemComponent.h"
#include "AbilitySystem/TssAttributeSet.h"
#include "GameFramework/Character.h"
#include "TssCharacterBase.generated.h"

USTRUCT(BlueprintType)
struct FTaggedMontage {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* montage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag montageTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 socketIndex; 
};

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
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Tss Character Base | References")
	TObjectPtr<UDataTable> defaultAttribues;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tss Character Base | References")
	TArray<FTaggedAbility> defaultAbilities; 

	UPROPERTY(EditDefaultsOnly, Category = "Tss Character Base | References")
	TArray<FTaggedMontage> abilityMontages;

	//-----------------------------------------------------------------------------------------
	// Protected Fields:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UPROPERTY(Transient)
	TObjectPtr<UTssAttributeSet> attributeSet;
	
	bool isDead; 
	
	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------

public:

	ATssCharacterBase();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
	
	//-----------------------------------------------------------------------------------------
	// Getters / Setters:
	//-----------------------------------------------------------------------------------------
	
public:
	
	TObjectPtr<UTssAbilitySystemComponent> GetAbilitySystemComponent() { return abilitySystemComponent; }
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------
	
public:

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetAbilityMontageByTag(const FGameplayTag& montageTag); 
	
	void Die(); 
	
	//-----------------------------------------------------------------------------------------
	// Protected Methods:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetSocketByIndex(int socketIndex);
	
	UFUNCTION(BlueprintPure)
	FVector GetFacingDirection(); 
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HandleDeath(); 
};
