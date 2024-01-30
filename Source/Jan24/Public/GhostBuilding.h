#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "GhostBuilding.generated.h"

/**
 * 
 */
UCLASS()
class JAN24_API AGhostBuilding : public ABuilding
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void InitializeGhost(UStaticMesh* BuildingMesh, UMaterialInterface* GhostMaterial);
};
