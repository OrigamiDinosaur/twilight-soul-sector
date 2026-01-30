// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Player/TssCharacterBase.h"
#include "TssGameplayAbility.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssGameplayAbility : public UGameplayAbility {
	GENERATED_BODY()

	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------

private:

	UPROPERTY(Transient)
	TObjectPtr<ATssCharacterBase> characterBase;

	//-----------------------------------------------------------------------------------------
	// Protected Methods:
	//-----------------------------------------------------------------------------------------
	
protected:

	UFUNCTION(BlueprintPure)
	ATssCharacterBase* GetCharacterBase();

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetAbilityMontage(); 
	
	UFUNCTION(BlueprintCallable)
	bool GetLiveCharactersWithinRadius(TArray<AActor*>& outOverlappingActors, const TArray<AActor*>& actorsToIgnore, const float radius, const FVector& origin);

	UFUNCTION(BlueprintPure)
	AActor* ReturnClosestTargetWithinRadius(const TArray<AActor*>& actorsToIgnore, const float radius, const FVector& origin);
	
	static void OrderByDistance(const FVector& origin, TArray<AActor*> inArray, TArray<AActor*>& outArray);
	
	float GetCost(const FGameplayAttribute& costAttribute, const float level = 1.0f) const;
	float GetManaCost(float level = 1.0f) const; 
	float GetStaminaCost(float level = 1.0f) const; 
	float GetHealthCost(float level = 1.0f) const;
	float GetCooldown(float level = 1.0f) const;
};
