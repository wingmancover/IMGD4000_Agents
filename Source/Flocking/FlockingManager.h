
#pragma once

#include "CoreMinimal.h"
#include "FlockingManager.generated.h"

UCLASS()
class FLOCKING_API UFlockingManager : public UObject
{

public:
	GENERATED_BODY()

	FVector UFlockingManager::Rule1(AAgent* boid); // Boids Rule1 Function

	void Init(UWorld* world, UStaticMeshComponent* mesh);
	void Flock();

private:
	UWorld* World;
	bool initialized;
	TArray<class AAgent*> Agents;
};
