// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
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
	// Unity Lifecycle:
	//-----------------------------------------------------------------------------------------
	
public:

	ATssProjectile();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
};
