
#pragma once

#include "Agent.h"
#include "CoreMinimal.h"
#include "FlockingManager.generated.h"

UCLASS()
class FLOCKING_API UFlockingManager : public UObject
{

public:
	GENERATED_BODY()

	FVector Rule1(AAgent* boid); // Boids Rule1 Function
	FVector Rule2(AAgent* boid); // Boids Rule2 Function
	FVector Rule3(AAgent* boid); // Boids Rule3 Function

	void Init(UWorld* world, UStaticMeshComponent* mesh);
	void Flock(float DeltaTime);

	FVector StrongWind(AAgent* boid);
	FVector TendToPlace(AAgent* boid, const FVector& place);

private:
	UWorld* World;
	bool initialized;
	TArray<class AAgent*> Agents;
};
