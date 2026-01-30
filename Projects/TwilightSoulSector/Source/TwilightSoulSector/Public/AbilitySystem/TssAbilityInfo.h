// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "TssAbilityInfo.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssAbilityInfo : public UDataAsset {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Public Properties:
	//-----------------------------------------------------------------------------------------

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> ability; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag abilityTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag montageTag;
};
