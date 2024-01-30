#include "GhostBuilding.h"

void AGhostBuilding::InitializeGhost(UStaticMesh* BuildingMesh, UMaterialInterface* GhostMaterial)
{
	GhostMesh = NewObject<UStaticMeshComponent>(this);
	GhostMesh->RegisterComponent();
	
	GhostMesh->SetStaticMesh(BuildingMesh);
	GhostMesh->SetMobility(EComponentMobility::Movable);
	GhostMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GhostMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	UpdateMaterial(GhostMaterial, GhostMesh);
	
	RootComponent = GhostMesh;
}

void AGhostBuilding::UpdateMaterial(UMaterialInterface* Material, UStaticMeshComponent* Mesh)
{
	const int32 MaterialSlots = Mesh->GetNumMaterials();
	for (int32 i = 0; i < MaterialSlots; i++)
	{
		Mesh->SetMaterial(i, Material);
	}
	
}

void AGhostBuilding::CheckForCollisions(UMaterialInterface* ValidMaterial, UMaterialInterface* InvalidMaterial)
{
	TArray<AActor*> OverlappingActors;
	GhostMesh->GetOverlappingActors(OverlappingActors);

	bool bIsOverlapping = OverlappingActors.Num() > 0;
	UMaterialInterface* CurrentMaterial = bIsOverlapping ? InvalidMaterial : ValidMaterial;
	UpdateMaterial(CurrentMaterial, GhostMesh);
}