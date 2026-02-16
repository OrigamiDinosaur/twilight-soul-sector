// Origami Dinosaur Creations 2026 (C)

#include "Interactions/Collectable.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TssCharacter.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

ACollectable::ACollectable() {
	PrimaryActorTick.bCanEverTick = true;
}

void ACollectable::BeginPlay() {
	Super::BeginPlay();
	
	state = ECollectibleStates::Idle; 
}

void ACollectable::Tick(const float DeltaTime) {
	Super::Tick(DeltaTime);
	
	UpdateStates(DeltaTime); 
}

//-----------------------------------------------------------------------------------------
// Blueprint Callable:
//-----------------------------------------------------------------------------------------

void ACollectable::OnOverlap(AActor* targetActor) {
	if (state != ECollectibleStates::Idle) return; 
	
	actorToTrack = targetActor; 
	
	ChangeStates(ECollectibleStates::Collecting);
}

//-----------------------------------------------------------------------------------------
// State Methods:
//-----------------------------------------------------------------------------------------

void ACollectable::ChangeStates(const ECollectibleStates newState) {
	if (state == newState) return; 
	
	state = newState; 
	
	switch (state) {
	case ECollectibleStates::Collected:
		StatesCollected_Enter();
		break;
	}
}

void ACollectable::UpdateStates(const float deltaTime) {
	
	switch (state) {
	case ECollectibleStates::Collecting:
		StatesCollecting_Update(deltaTime);
		break;
	case ECollectibleStates::Collected:
		StatesCollected_Update(); 
		break;
	}
}

void ACollectable::StatesCollecting_Update(const float deltaTime) {
	
	FVector moveDirection = actorToTrack->GetActorLocation() - GetActorLocation();
	moveDirection.Normalize();

	const FVector newLocation = GetActorLocation() + (moveDirection * collectMoveSpeed * deltaTime); 	
	SetActorLocation(newLocation);

	const float distanceFromTarget = FVector::Distance(actorToTrack->GetActorLocation(), GetActorLocation());
	
	if (distanceFromTarget < collectThreshold) {
		ChangeStates(ECollectibleStates::Collected); 
	}
}

void ACollectable::StatesCollected_Enter() {
	
	collectedEndTime = GetWorld()->GetTimeSeconds() + collectedDuration;

	Collected_BP();
	
	if (ATssCharacter* character = Cast<ATssCharacter>(actorToTrack)) {
		character->Collect(collectionTag, collectionMagnitude);		
	}
	
	if (collectedSystem) UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, collectedSystem, GetActorLocation()); 
	if (collectedSfx) UGameplayStatics::PlaySoundAtLocation(this, collectedSfx, GetActorLocation()); 
}

void ACollectable::StatesCollected_Update() {
	
	if (IsValid(this) && GetWorld()->GetTimeSeconds() > collectedEndTime) {
		Destroy(); 
	}
}
