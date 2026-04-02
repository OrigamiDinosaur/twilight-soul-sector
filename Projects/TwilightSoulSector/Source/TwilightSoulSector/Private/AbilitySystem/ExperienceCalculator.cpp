// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/ExperienceCalculator.h"
#include "Debug/DebugLog.h"

//-----------------------------------------------------------------------------------------
// UE Lifecycle:
//-----------------------------------------------------------------------------------------

void UExperienceCalculator::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	
	LOG("Experience Calculator Initialized")
}

void UExperienceCalculator::Deinitialize() {
	Super::Deinitialize();
}

//-----------------------------------------------------------------------------------------
// Public Methods:
//-----------------------------------------------------------------------------------------

int UExperienceCalculator::GetExpReward(const int enemyLevel) const {
	
	if (FMath::Abs(playerLevel - enemyLevel) < MAX_LEVEL_DISPARITY) {
		
		return expTable->FindCurve(MID_REWARDS_TABLE, FString())->Eval(enemyLevel); 
	}
	
	if (enemyLevel < playerLevel) return expTable->FindCurve(LOW_REWARDS_TABLE, FString())->Eval(enemyLevel); 
	else return expTable->FindCurve(HIGH_REWARDS_TABLE, FString())->Eval(enemyLevel); 
}

int UExperienceCalculator::GetThresholdForLevel(const int level) const {
	
	return expTable->FindCurve(THRESHOLDS_TABLE, FString())->Eval(level + 1); 
}
