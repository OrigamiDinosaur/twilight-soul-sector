// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "Collectable.h"
#include "NiagaraSystem.h"
#include "AbilitySystem/TssEffectActor.h"
#include "TssCollectableEffectActor.generated.h"


UCLASS()
class TWILIGHTSOULSECTOR_API ATssCollectableEffectActor : public ATssEffectActor {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------
		
protected: 
	
	UPROPERTY(EditDefaultsOnly, Category = "Collectable")
	float collectMoveSpeed;
	
	UPROPERTY(EditDefaultsOnly, Category = "Collectable")
	float collectThreshold;
	
	UPROPERTY(EditDefaultsOnly, Category = "Collectable")
	float collectedDuration; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Collectable")
	UNiagaraSystem* collectedSystem; 
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Collectable")
	bool isPlacedInWorld;
	
	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------
	
private:
	
	ECollectibleStates state; 
	
	UPROPERTY(Transient)
	AActor* actorToTrack; 
	
	float collectedEndTime; 
	
	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------
		
public: 
	
	ATssCollectableEffectActor();
	
protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
	
	//-----------------------------------------------------------------------------------------
	// Blueprint Methods:
	//-----------------------------------------------------------------------------------------

protected:
	
	UFUNCTION(BlueprintCallable)
	void OnCollectableOverlap(AActor* targetActor);

	UFUNCTION(BlueprintImplementableEvent)
	void Collected_BP(); 
	
	//-----------------------------------------------------------------------------------------
	// Public Methods:
	//-----------------------------------------------------------------------------------------
	
public: 
	
	void SpawnCollectable(); 
	
	//-----------------------------------------------------------------------------------------
	// State Methods:
	//-----------------------------------------------------------------------------------------
	
protected:	
	
	UFUNCTION(BlueprintCallable)
	void ChangeStates(ECollectibleStates newState);
	
private:
	
	void UpdateStates(const float deltaTime); 
	
protected:
	
	UFUNCTION(BlueprintImplementableEvent)
	void StateSpawning_Enter_BP(); 
	
	UFUNCTION(BlueprintImplementableEvent)
	void StateSpawning_Update_BP(const float deltaTime);
	
	UFUNCTION(BlueprintImplementableEvent)
	void StateIdle_Update_BP(const float deltaTime); 
	
private: 
	
	void StatesCollecting_Update(const float deltaTime); 
	void StatesCollected_Enter(); 
	void StatesCollected_Update(); 
};
