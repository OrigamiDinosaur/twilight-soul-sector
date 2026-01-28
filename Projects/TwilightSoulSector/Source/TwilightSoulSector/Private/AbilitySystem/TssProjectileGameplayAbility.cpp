// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssProjectileGameplayAbility.h"

//-----------------------------------------------------------------------------------------
// Blueprint Callable Methods:
//-----------------------------------------------------------------------------------------

void UTssProjectileGameplayAbility::SpawnProjectile(const FVector& spawnLocation, const FRotator spawnRotation) {
	
	FTransform spawnTransform; 
	spawnTransform.SetLocation(spawnLocation);
	spawnTransform.SetRotation(spawnRotation.Quaternion()); 
	
	TObjectPtr<ATssProjectile> projectile = GetWorld()->SpawnActorDeferred<ATssProjectile>(projectileAsset, spawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	projectile->FinishSpawning(spawnTransform); 
}
