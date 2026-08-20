// Origami Dinosaur Creations 2026 (C)

#include "Interactions/TssCollectableEffectActor.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------
	
void ATssCollectableEffectActor::BeginPlay() {
	Super::BeginPlay();
	
	if (isPlacedInWorld) ChangeStates(ECollectibleStates::Idle); 
}

void ATssCollectableEffectActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	UpdateStates(DeltaTime); 
}

//-----------------------------------------------------------------------------------------
// Blueprint Methods:
//-----------------------------------------------------------------------------------------

void ATssCollectableEffectActor::OnCollectableOverlap(AActor* targetActor) {
	if (state != ECollectibleStates::Idle) return; 
	
	actorToTrack = targetActor; 
	
	ChangeStates(ECollectibleStates::Collecting);
}

//-----------------------------------------------------------------------------------------
// State Methods:
//-----------------------------------------------------------------------------------------

void ATssCollectableEffectActor::ChangeStates(ECollectibleStates newState) {
	if (state == newState) return; 
	
	state = newState; 
	
	switch (state) {
	case ECollectibleStates::Spawning:
		StateSpawning_Enter_BP();
		break;
	case ECollectibleStates::Collected:
		StatesCollected_Enter();
		break;
	}
}

void ATssCollectableEffectActor::UpdateStates(const float deltaTime) {
	
	switch (state) {
	case ECollectibleStates::Spawning:
		StateSpawning_Update_BP(deltaTime);
		break;
	case ECollectibleStates::Idle:
		StateIdle_Update_BP(deltaTime); 
		break;
	case ECollectibleStates::Collecting:
		StatesCollecting_Update(deltaTime);
		break;
	case ECollectibleStates::Collected:
		StatesCollected_Update(); 
		break;
	}
}

void ATssCollectableEffectActor::StatesCollecting_Update(const float deltaTime) {
	
	FVector moveDirection = actorToTrack->GetActorLocation() - GetActorLocation();
	moveDirection.Normalize();

	const FVector newLocation = GetActorLocation() + (moveDirection * collectMoveSpeed * deltaTime); 	
	SetActorLocation(newLocation);

	const float distanceFromTarget = FVector::Distance(actorToTrack->GetActorLocation(), GetActorLocation());
	
	if (distanceFromTarget < collectThreshold) {
		ChangeStates(ECollectibleStates::Collected); 
	}
}

void ATssCollectableEffectActor::StatesCollected_Enter() {
	
	collectedEndTime = GetWorld()->GetTimeSeconds() + collectedDuration;

	Collected_BP();
	
	if (instantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap) {
		ApplyEffectToTarget(actorToTrack, instantGameplayEffectClass);
	}

	if (durationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap) {
		ApplyEffectToTarget(actorToTrack, durationGameplayEffectClass);
	}

	if (infiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap) {
		ApplyEffectToTarget(actorToTrack, infiniteGameplayEffectClass);
	}
		
	if (collectedSystem) UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, collectedSystem, GetActorLocation()); 
	if (collectedSfx) UGameplayStatics::PlaySoundAtLocation(this, collectedSfx, GetActorLocation()); 
}

void ATssCollectableEffectActor::StatesCollected_Update() {
	
	if (IsValid(this) && GetWorld()->GetTimeSeconds() > collectedEndTime) {
		Destroy(); 
	}
}
