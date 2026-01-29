// Origami Dinosaur Creations 2026 (C)

#include "AbilitySystem/TssProjectile.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TssCharacterBase.h"
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
	
	SetLifeSpan(maxLifeSpan); 
	collision->OnComponentBeginOverlap.AddDynamic(this, &ATssProjectile::Collision_OnBeginOverlap); 
}

void ATssProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

//-----------------------------------------------------------------------------------------
// Event Handlers:
//-----------------------------------------------------------------------------------------

void ATssProjectile::Collision_OnBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool fromSweep, const FHitResult& sweepResult) {
	if (hasCollided) return; 
	
	hasCollided = true; 
	
	if (impactSound) UGameplayStatics::PlaySoundAtLocation(this, impactSound, GetActorLocation(), FRotator(0.0f));
	if (impactSystem) UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, impactSystem, GetActorLocation()); 
	
	// todo: apply gameplay effect. 
	if (TObjectPtr<ATssCharacterBase> characterBase = Cast<ATssCharacterBase>(otherActor)) {
		
		characterBase->GetAbilitySystemComponent()->ApplySimpleGameplayEffect(damageEffectAsset); 
	}	
	
	Destroy(); 
	
}
