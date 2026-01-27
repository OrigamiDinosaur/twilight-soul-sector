// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Debug/DebugLog.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

ATssEffectActor::ATssEffectActor() {
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

//-----------------------------------------------------------------------------------------
// Blueprint Callable:
//-----------------------------------------------------------------------------------------

void ATssEffectActor::ApplyEffectToTarget(AActor* targetActor, const TSubclassOf<UGameplayEffect> gameplayEffectClass) {
	
	TArray<FGameplayTag> ignoreTags;
	tagsToIgnore.GetGameplayTagArray(ignoreTags);

	for (FGameplayTag& ignoreTag : ignoreTags) {
		if (targetActor->ActorHasTag(*ignoreTag.ToString())) {
			return; 
		}
	}
	
	// try and find an asc. 
	UAbilitySystemComponent* asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(targetActor);

	// if no asc, return. 
	if (!asc) {
		LOGERROR("AbilitySystemComponent not found in TssEffectActor");
		return; 
	}

	if (!gameplayEffectClass) {
		LOGERROR("GameplayEffectClass not found in TssEffectorActor"); 
		return;
	}

	// create our context
	FGameplayEffectContextHandle contextHandle = asc->MakeEffectContext();
	contextHandle.AddSourceObject(this);

	// create our spec handle
	const FGameplayEffectSpecHandle effectSpecHandle = asc->MakeOutgoingSpec(gameplayEffectClass, actorLevel, contextHandle);

	// use the spec handle to apply the effect. 
	FActiveGameplayEffectHandle activeEffectHandle = asc->ApplyGameplayEffectSpecToSelf(*effectSpecHandle.Data.Get());

	const bool isInfinite = effectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;

	if (isInfinite && infiniteEffectRemovalPolicy == EEffectRemovePolicy::RemoveOnEndOverlap) {
		activeEffectHandles.Add(activeEffectHandle, asc);
	}

	if (destroyOnEffectApplication && !isInfinite) {
		Destroy(); 
	}
}

void ATssEffectActor::OnOverlap(AActor* targetActor) {

	if (instantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap) {
		ApplyEffectToTarget(targetActor, instantGameplayEffectClass);
	}

	if (durationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap) {
		ApplyEffectToTarget(targetActor, durationGameplayEffectClass);
	}

	if (infiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap) {
		ApplyEffectToTarget(targetActor, infiniteGameplayEffectClass);
	}
}

void ATssEffectActor::OnEndOverlap(AActor* targetActor) {
	TArray<FGameplayTag> ignoreTags;
	tagsToIgnore.GetGameplayTagArray(ignoreTags);

	for (FGameplayTag& ignoreTag : ignoreTags) {
		if (targetActor->ActorHasTag(*ignoreTag.ToString())) {
			return; 
		}
	}
	
	if (instantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
		ApplyEffectToTarget(targetActor, instantGameplayEffectClass);
	}

	if (durationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
		ApplyEffectToTarget(targetActor, durationGameplayEffectClass);
	}
	
	if (infiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
		ApplyEffectToTarget(targetActor, infiniteGameplayEffectClass);
	}

	if (infiniteEffectRemovalPolicy == EEffectRemovePolicy::RemoveOnEndOverlap) {

		UAbilitySystemComponent* asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(targetActor);
		if (!IsValid(asc)) return;

		TArray<FActiveGameplayEffectHandle> handlesToRemove;

		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> activeEffectHandle : activeEffectHandles) {
			if (asc == activeEffectHandle.Value) {

				asc->RemoveActiveGameplayEffect(activeEffectHandle.Key, stacksToRemove);
				handlesToRemove.Add(activeEffectHandle.Key); 
			}
		}

		for (FActiveGameplayEffectHandle& handle : handlesToRemove) {
			activeEffectHandles.FindAndRemoveChecked(handle); 
		}
	}
}
