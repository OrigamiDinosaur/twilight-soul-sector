// Origami Dinosaur Creations 2026 (C)

#include "Agents/TssAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

ATssAIController::ATssAIController() {
	
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard Component");
	behaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("Behavior Tree Component");
}
