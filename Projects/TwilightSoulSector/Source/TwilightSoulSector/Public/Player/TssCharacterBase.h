// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TssCharacterBase.generated.h"

UCLASS()
class TWILIGHTSOULSECTOR_API ATssCharacterBase : public ACharacter {
	GENERATED_BODY()

	//-----------------------------------------------------------------------------------------
	// Unreal Lifecycle:
	//-----------------------------------------------------------------------------------------

public:

	ATssCharacterBase();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

};
