
#include "FlockingManager.h"
#include "Agent.h"

#define AGENT_COUNT 10    

void UFlockingManager::Init(UWorld* world, UStaticMeshComponent* mesh) {
    UE_LOG(LogTemp, Warning, TEXT("MANAGER INIT"));

    World = world;

    float incr = (PI * 2.f) / AGENT_COUNT;
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (World != nullptr) {
            FRotator rotation = FRotator();

            FVector location = FVector();
            location.X = FMath::Sin(incr * i) * 150.f;
            location.Z = FMath::Cos(incr * i) * 150.f;

            AAgent* agent = World->SpawnActor<AAgent>(location, rotation);
            agent->Init(mesh, i);
            Agents.Add(agent);
        }
    }

    initialized = true;
}

FVector UFlockingManager::Rule1(AAgent* boid) {
    FVector perceivedCenter = FVector(0, 0, 0);
    int count = 0;

    // Calculate the perceived center of all other boids
    for (auto& other : Agents) {
        if (other != boid) {
            perceivedCenter += other->GetActorLocation();
            count++;
        }
    }

    if (count > 0) {
        perceivedCenter /= count; // Average position
        return (perceivedCenter - boid->GetActorLocation()) / 100.0f; // Move 1% towards the perceived center
    }

    return FVector(0, 0, 0); // No adjustment if alone
}


void UFlockingManager::Flock() {
    TArray<FVector> velocities;
    velocities.SetNum(Agents.Num());

    for (int i = 0; i < Agents.Num(); i++) {
        FVector v1 = Rule1(Agents[i]);
        velocities[i] = Agents[i]->Velocity + v1;
    }

    // Update boid positions based on new velocities
    for (int i = 0; i < Agents.Num(); i++) {
        Agents[i]->Velocity = velocities[i];
        FVector newLocation = Agents[i]->GetActorLocation() + Agents[i]->Velocity;
        Agents[i]->SetActorLocation(newLocation);
    }
}
