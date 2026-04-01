// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ExperienceCalculator.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UExperienceCalculator : public UWorldSubsystem {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Constants:
	//-----------------------------------------------------------------------------------------
	
	inline static const FName THRESHOLDS_TABLE = TEXT("Thresholds");
	inline static const FName LOW_REWARDS_TABLE = TEXT("LowReward");
	inline static const FName MID_REWARDS_TABLE = TEXT("MidReward");
	inline static const FName HIGH_REWARDS_TABLE = TEXT("HighReward");
	
	static constexpr int MAX_LEVEL_DISPARITY = 2; 
	
	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------
	
private:
	
	UPROPERTY(Transient)
	TObjectPtr<UCurveTable> expTable; 
	
	int playerLevel; 
	
	//-----------------------------------------------------------------------------------------
	// UE Lifecycle:
	//-----------------------------------------------------------------------------------------

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	void SetExpTable(const TObjectPtr<UCurveTable> inExpTable) { expTable = inExpTable; }
	void SetPlayerLevel(const int inPlayerLevel) { playerLevel = inPlayerLevel; }
	int GetExpReward(const int enemyLevel) const; 
	int GetThresholdForLevel(const int level) const;
};
