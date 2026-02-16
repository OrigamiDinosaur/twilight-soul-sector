// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "TssEffectActor.generated.h"

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8 {
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNoApply
};

UENUM(BlueprintType)
enum class EEffectRemovePolicy : uint8 {
	RemoveOnEndOverlap,
	DoNoRemove
};

UCLASS()
class TWILIGHTSOULSECTOR_API ATssEffectActor : public AActor {
	GENERATED_BODY()

	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	float actorLevel = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> instantGameplayEffectClass;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy instantEffectApplicationPolicy = EEffectApplicationPolicy::DoNoApply;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> durationGameplayEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy durationEffectApplicationPolicy = EEffectApplicationPolicy::DoNoApply;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> infiniteGameplayEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy infiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNoApply;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	EEffectRemovePolicy infiniteEffectRemovalPolicy = EEffectRemovePolicy::RemoveOnEndOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	FGameplayTagContainer tagsToIgnore; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	int stacksToRemove;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Applied Effects")
	bool destroyOnEffectApplication; 

	//-----------------------------------------------------------------------------------------
    // Private Fields:
    //-----------------------------------------------------------------------------------------

private:

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> activeEffectHandles;
	
	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------
	
public:
	
	ATssEffectActor();
	
	//-----------------------------------------------------------------------------------------
	// Blueprint Callable:
	//-----------------------------------------------------------------------------------------

protected:

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* targetActor, TSubclassOf<UGameplayEffect> gameplayEffectClass);
		
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* targetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* targetActor);
};
