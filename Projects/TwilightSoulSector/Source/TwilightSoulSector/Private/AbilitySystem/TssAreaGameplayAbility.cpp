// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssAreaGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"

//-----------------------------------------------------------------------------------------
// Protected Methods:
//-----------------------------------------------------------------------------------------

void UTssAreaGameplayAbility::ApplyEffectInRadius() {
	
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(GetAvatarActorFromActorInfo());
	
	TArray<AActor*> overlappingActors;
	if (GetLiveCharactersWithinRadius(overlappingActors, actorsToIgnore, radius, GetAvatarActorFromActorInfo()->GetActorLocation())) {
		
		for (AActor* actor : overlappingActors) {
			
			if (UAbilitySystemComponent* asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(actor)) {
				
				if (UTssAbilitySystemComponent* tssAsc = Cast<UTssAbilitySystemComponent>(asc)) {
					
					tssAsc->ApplySimpleGameplayEffect(effectToApply); 
				}
			}
		}
	}
}

void UTssAreaGameplayAbility::ApplyDamageInRadius(float damage) {
	
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(GetAvatarActorFromActorInfo());
	
	TArray<AActor*> overlappingActors;
	if (GetLiveCharactersWithinRadius(overlappingActors, actorsToIgnore, radius, GetAvatarActorFromActorInfo()->GetActorLocation())) {
		
		for (AActor* actor : overlappingActors) {
			
			if (UAbilitySystemComponent* asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(actor)) {
				
				if (UTssAbilitySystemComponent* tssAsc = Cast<UTssAbilitySystemComponent>(asc)) {
					
					tssAsc->ApplyDamageEffect(effectToApply, damage); 
				}
			}
		}
	}
}
