// Fill out your copyright notice in the Description page of Project Settings.


#include "Graveyard.h"

#include "Enemy.h"

// Sets default values
AGraveyard::AGraveyard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGraveyard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGraveyard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGraveyard::SpawnEnemy()
{
	if (GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		FVector SpawnLocation = GetSpawnLocation();
		FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

		AEnemy* SpawnedEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
	}
}

FVector AGraveyard::GetSpawnLocation()
{
	// Find the SpawnPoint component
	USceneComponent* SpawnPoint = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("SpawnPoint")));

	if (SpawnPoint)
	{
		// Return the world location of the SpawnPoint
		FVector SpawnLocation = SpawnPoint->GetComponentLocation();
		return SpawnLocation;
	}

	// Fallback to the actor's location if SpawnPoint is not found
	return GetActorLocation();
}
