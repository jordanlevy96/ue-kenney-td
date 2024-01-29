// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Graveyard.generated.h"

UCLASS()
class JAN24_API AGraveyard : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AGraveyard();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Gets the transform position of the spawn
	FVector GetSpawnLocation();

	// Spawn a skeleton at the SpawnPoint TODO: genericise for other enemies
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AEnemy> EnemyToSpawn;
};
