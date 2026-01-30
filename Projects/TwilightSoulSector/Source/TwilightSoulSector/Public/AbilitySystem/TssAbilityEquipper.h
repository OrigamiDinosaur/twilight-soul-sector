// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "TssAbilityInfo.h"
#include "GameFramework/Actor.h"
#include "TssAbilityEquipper.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API ATssAbilityEquipper : public AActor {
	GENERATED_BODY()

	//-----------------------------------------------------------------------------------------
	// Inspector Variables:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UPROPERTY(EditInstanceOnly, Category = "Ability Equipper")
	TObjectPtr<UTssAbilityInfo> abilityToEquip; 
	
	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------
	
public:

	ATssAbilityEquipper();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
	
	//-----------------------------------------------------------------------------------------
	// Protected Methods:
	//-----------------------------------------------------------------------------------------
	
protected:
	
	UFUNCTION(BlueprintCallable)
	void AttemptAllowCharacterEquip(AActor* actor); 
	
	UFUNCTION(BlueprintCallable)
	void AttemptDisableCharacterEquip(AActor* actor); 
};
