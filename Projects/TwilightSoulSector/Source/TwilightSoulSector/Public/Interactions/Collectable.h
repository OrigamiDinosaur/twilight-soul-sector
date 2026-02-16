// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

UENUM(BlueprintType)
enum class ECollectibleStates : uint8 {
	Idle,
	Collecting,
	Collected
};

UCLASS()
class TWILIGHTSOULSECTOR_API ACollectable : public AActor {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------
		
protected: 
	
	UPROPERTY(EditDefaultsOnly, Category = "Collectable")
	FGameplayTag collectionTag;
	
	UPROPERTY(EditDefaultsOnly, Category = "Collectable")
	int collectionMagnitude;
	
	UPROPERTY(EditDefaultsOnly, Category = "Collectable")
	float collectMoveSpeed;
	
	UPROPERTY(EditDefaultsOnly, Category = "Collectable")
	float collectThreshold;
	
	UPROPERTY(EditDefaultsOnly, Category = "Collectable")
	float collectedDuration; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Collectable")
	UNiagaraSystem* collectedSystem; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Collectable")
	USoundBase* collectedSfx; 
	
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
	
	ACollectable();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
	
	//-----------------------------------------------------------------------------------------
	// Blueprint Methods:
	//-----------------------------------------------------------------------------------------

protected:
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* targetActor);

	UFUNCTION(BlueprintImplementableEvent)
	void Collected_BP(); 
	
	//-----------------------------------------------------------------------------------------
	// State Methods:
	//-----------------------------------------------------------------------------------------
	
private:
	
	void ChangeStates(ECollectibleStates newState);
	void UpdateStates(const float deltaTime); 
	
	void StatesCollecting_Update(const float deltaTime); 
	void StatesCollected_Enter(); 
	void StatesCollected_Update(); 
};
