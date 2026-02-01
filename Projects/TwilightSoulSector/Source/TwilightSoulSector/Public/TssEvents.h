// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TssAbilityInfo.h"
#include "UObject/NoExportTypes.h"
#include "TssEvents.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActionDelegate); 

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoDelegate, UTssAbilityInfo*, info);

UCLASS()
class TWILIGHTSOULSECTOR_API UTssEvents : public UObject {
	GENERATED_BODY()
};
