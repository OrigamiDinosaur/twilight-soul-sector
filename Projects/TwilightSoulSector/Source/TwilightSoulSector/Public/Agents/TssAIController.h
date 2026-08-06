// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "TssAIController.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API ATssAIController : public AAIController {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Components:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Behaviours")
	TObjectPtr<UBehaviorTreeComponent> behaviorTreeComponent; 
	
	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------
	
public:
	
	ATssAIController(); 
};
