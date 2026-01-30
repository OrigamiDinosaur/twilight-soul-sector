// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "TssProjectile.h"
#include "AbilitySystem/TssGameplayAbility.h"
#include "TssProjectileGameplayAbility.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API UTssProjectileGameplayAbility : public UTssGameplayAbility {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------

protected: 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Ability | References")
	TSubclassOf<ATssProjectile> projectileAsset;
	
	//-----------------------------------------------------------------------------------------
	// Blueprint Callable Methods:
	//-----------------------------------------------------------------------------------------
	
protected: 
	
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& spawnLocation, const FRotator spawnRotation); 
	
	UFUNCTION(BlueprintCallable)
	void SpawnHomingProjectile(const FVector& spawnLocation, const FRotator spawnRotation, USceneComponent* homingTarget); 
	
	UFUNCTION(BlueprintCallable)
	void FindTargetWithinRadiusAndSpawnHomingProjectile(const FVector& spawnLocation, const FRotator spawnRotation, float targetRadius);
};
