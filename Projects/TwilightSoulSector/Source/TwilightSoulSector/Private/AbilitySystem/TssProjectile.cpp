// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssProjectile.h"

#include "TwilightSoulSector/TwilightSoulSector.h"

//-----------------------------------------------------------------------------------------
// Unity Lifecycle:
//-----------------------------------------------------------------------------------------

ATssProjectile::ATssProjectile() {
	PrimaryActorTick.bCanEverTick = true;
	
	collision = CreateDefaultSubobject<USphereComponent>("Collision");
	SetRootComponent(collision);
	collision->SetCollisionObjectType(ECC_Projectile);
	collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	projectileMovementComponent->InitialSpeed = 550.0f;
	projectileMovementComponent->MaxSpeed = 550.0f;
	projectileMovementComponent->ProjectileGravityScale = 0.0f; 
}

void ATssProjectile::BeginPlay() {
	Super::BeginPlay();
}

void ATssProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
