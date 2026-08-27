// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TssAbilitySystemLibrary.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssAbilitySystemLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------
	
public:
	
	UFUNCTION(BlueprintPure, Category = "Tss Ability System Library")
	static bool GetGameplayTagFromName(FName inName, FGameplayTag& tag); 
	
	UFUNCTION(BlueprintCallable, Category = "Tss Ability System Library")
	static void TryActivateAbilityWithTag(UAbilitySystemComponent* asc, const TSubclassOf<UGameplayAbility> ability, const FGameplayTag tag);
};
