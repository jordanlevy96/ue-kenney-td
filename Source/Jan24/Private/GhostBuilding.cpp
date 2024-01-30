#include "GhostBuilding.h"

void AGhostBuilding::InitializeGhost(UStaticMesh* BuildingMesh, UMaterialInterface* GhostMaterial)
{
	if (BuildingMesh)
	{
		UStaticMeshComponent* GhostMesh = NewObject<UStaticMeshComponent>(this);
		GhostMesh->SetStaticMesh(BuildingMesh);
		GhostMesh->RegisterComponent();
		GhostMesh->SetMobility(EComponentMobility::Movable);
		GhostMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Apply the ghost material to all material slots
		const int32 MaterialSlots = GhostMesh->GetNumMaterials();
		for (int32 i = 0; i < MaterialSlots; i++)
		{
			GhostMesh->SetMaterial(i, GhostMaterial);
		}

		if (RootComponent == nullptr)
		{
			RootComponent = GhostMesh;
		}
		else
		{
			GhostMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}