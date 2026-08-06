// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssProjectileGameplayAbility.h"

#include "Debug/DebugLog.h"

//-----------------------------------------------------------------------------------------
// Blueprint Callable Methods:
//-----------------------------------------------------------------------------------------

void UTssProjectileGameplayAbility::SpawnProjectile(const FVector& spawnLocation, const FRotator spawnRotation, bool isPlayer) {
	
	FTransform spawnTransform; 
	spawnTransform.SetLocation(spawnLocation);
	spawnTransform.SetRotation(spawnRotation.Quaternion()); 
	
	TObjectPtr<ATssProjectile> projectile = GetWorld()->SpawnActorDeferred<ATssProjectile>(projectileAsset, spawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	projectile->SetCollisionTarget(!isPlayer); 
	projectile->FinishSpawning(spawnTransform); 	
}

void UTssProjectileGameplayAbility::SpawnHomingProjectile(const FVector& spawnLocation, const FRotator spawnRotation, USceneComponent* homingTarget, bool isPlayer) {
	
	FTransform spawnTransform; 
	spawnTransform.SetLocation(spawnLocation);
	spawnTransform.SetRotation(spawnRotation.Quaternion()); 
	
	TObjectPtr<ATssProjectile> projectile = GetWorld()->SpawnActorDeferred<ATssProjectile>(projectileAsset, spawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	projectile->SetHomingTarget(homingTarget); 
	projectile->SetCollisionTarget(!isPlayer); 
	
	projectile->FinishSpawning(spawnTransform); 
}

void UTssProjectileGameplayAbility::FindTargetWithinRadiusAndSpawnHomingProjectile(const FVector& spawnLocation, const FRotator spawnRotation, const float targetRadius) {
	
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(GetAvatarActorFromActorInfo());
	
	if (const AActor* target = ReturnClosestTargetWithinRadius(actorsToIgnore, targetRadius, GetAvatarActorFromActorInfo()->GetActorLocation())) {		
		SpawnHomingProjectile(spawnLocation, spawnRotation, target->GetRootComponent());
	}
	else {		
		SpawnProjectile(spawnLocation, spawnRotation); 
	}
}
