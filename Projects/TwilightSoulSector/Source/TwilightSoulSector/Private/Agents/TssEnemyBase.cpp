// Origami Dinosaur Creations 2026 (C)

#include "Agents/TssEnemyBase.h"

#include "AbilitySystem/TssGameplayTags.h"
#include "Agents/TssDummyAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Debug/DebugLog.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Interactions/TssCollectableEffectActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

//-----------------------------------------------------------------------------------------
// Unreal Lifecycle:
//-----------------------------------------------------------------------------------------

void ATssEnemyBase::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);
	
	// cache our controller. 
	aiController = Cast<ATssAIController>(NewController); 
	
	if (!aiController) {
		LOGERROR("AI Controller not found!");
	}
	else {
		
		// initialize our blackoard.
		blackboardComponent = aiController->GetBlackboardComponent();
		blackboardComponent->InitializeBlackboard(*behaviourTree->BlackboardAsset); 
		
		// do any blueprint initialization.
		InitBlackboard_BP();
		
		// run our behaviour.
		aiController->RunBehaviorTree(behaviourTree); 
	}	
	
	animInstance = Cast<UTssDummyAnimInstance>(GetMesh()->GetAnimInstance()); 
	
	if (!animInstance) {
		LOGERROR("AnimInstance not found in TssDummy");
	}
	
	for (const TObjectPtr<UTssAbilityInfo>& info : enemyAbilities) {
		EquipAbility(info);
	}
	
	totalSpawnWeight = 0; 
		
	for (FLoot& loot : lootDrops) {
			
		totalSpawnWeight += loot.spawnWeight;		
		loot.adjustedSpawnWeight = totalSpawnWeight;
	}
}

void ATssEnemyBase::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	
	if (isDead) return; 
	
	const float currentSpeed = GetMovementComponent()->Velocity.Length(); 
	
	const float normalizedSpeed = UKismetMathLibrary::NormalizeToRange(currentSpeed, 0.0f, GetMovementComponent()->GetMaxSpeed());
	
	if (animInstance) animInstance->SetLocomotionSpeed(normalizedSpeed); 
}

//-----------------------------------------------------------------------------------------
// Protected Methods:
//-----------------------------------------------------------------------------------------

FVector ATssEnemyBase::GetSocketByIndex_Implementation(const int socketIndex) {
	return GetMesh()->GetSocketLocation(sockets[socketIndex]); 
}

void ATssEnemyBase::HandleDeath_Implementation() {
	if (animInstance) animInstance->SetShouldDie(true); 
	
	aiController->GetBlackboardComponent()->SetValueAsBool(deadValueName, true); 
	
	SpawnExp();
	
	SpawnLoot();
	
	SetActorEnableCollision(false); 
}

void ATssEnemyBase::HandleIsHit() {
	
	aiController->GetBlackboardComponent()->SetValueAsBool(hitValueName, isHit); 
}

void ATssEnemyBase::SpawnLoot() {
	if (lootDropChance == 0 || lootDrops.Num() == 0) return;

	const float lootDropAttempt = FMath::RandRange(0.0f, 100.0f);

	if (lootDropAttempt < lootDropChance) {
							
		const float lootSpawnRand = FMath::RandRange(0.0f, totalSpawnWeight); 
		
		int spawnIndex = -1; 
		
		for (int i = 0; i < lootDrops.Num(); i++) {
			
			if (lootSpawnRand < lootDrops[i].adjustedSpawnWeight) {
				spawnIndex = i; 
				break; 
			}
		}
		
		if (spawnIndex != -1) {
			
			const float spawnDegree = FMath::RandRange(0.0f, 360.0f); 
			
			FVector spawnLocation = GetSpawnPosition(spawnDistanceMin, spawnDistanceMax, spawnDegree);
			FRotator spawnRotation = FRotator(0.0f); 
			
			AActor* lootDrop = GetWorld()->SpawnActor<AActor>(lootDrops[spawnIndex].lootAsset, spawnLocation, spawnRotation);

			if (ATssCollectableEffectActor* effectLoot = Cast<ATssCollectableEffectActor>(lootDrop)) {				
				effectLoot->SpawnCollectable();
			}
		}
	}
}

//-----------------------------------------------------------------------------------------
// Private Methods:
//-----------------------------------------------------------------------------------------

void ATssEnemyBase::EquipAbility(const TObjectPtr<UTssAbilityInfo>& abilityInfo) {
	
	const FTssGameplayTags tags = FTssGameplayTags::Get();
	
	FGameplayTag montageTag = abilityInfo->montageTag;
	
	if (montageTag == tags.Montage_Arms) {
		montageTag = tags.Montage_Arms_Primary; 
	}
	
	abilitySystemComponent->AddCharacterAbility(abilityInfo->ability, montageTag); 
}
