// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "NiagaraSystem.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TssProjectile.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API ATssProjectile : public AActor {
	GENERATED_BODY()
	
	//-----------------------------------------------------------------------------------------
	// Components:
	//-----------------------------------------------------------------------------------------

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile | Components")
	TObjectPtr<USphereComponent> collision; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile | Components")
	TObjectPtr<UProjectileMovementComponent> projectileMovementComponent; 
	
	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile | References")
	TSubclassOf<UGameplayEffect> damageEffectAsset;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile | References")
	TObjectPtr<UNiagaraSystem> impactSystem;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile | References")
	TObjectPtr<USoundBase> impactSound; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile | Lifespan")
	float maxLifeSpan; 
	
	//-----------------------------------------------------------------------------------------
	// Private Fields:
	//-----------------------------------------------------------------------------------------
	
private:
	
	bool hasCollided; 
	
	//-----------------------------------------------------------------------------------------
	// Unity Lifecycle:
	//-----------------------------------------------------------------------------------------
	
public:

	ATssProjectile();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
	
	//-----------------------------------------------------------------------------------------
	// Event Handlers:
	//-----------------------------------------------------------------------------------------

private:

	UFUNCTION()
	void Collision_OnBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool fromSweep, const FHitResult& sweepResult);

};
