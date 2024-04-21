
#include "FlockingManager.h"
#include "Agent.h"
#include "DrawDebugHelpers.h"


#define AGENT_COUNT 10    
#define MAX_SPEED 100.f

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

// Rule 1: Boids try to fly towards the centre of mass of neighbouring boids.
FVector UFlockingManager::Rule1(AAgent* boid) {
    FVector perceivedCenter = FVector(0, 0, 0);
    int count = 0;

    for (auto& other : Agents) {
        if (other != boid) {
            perceivedCenter += other->GetActorLocation();
            count++;
        }
    }

    if (count > 0) {
        perceivedCenter /= count;
        return (perceivedCenter - boid->GetActorLocation()) / 100.0f;
    }

    return FVector(0, 0, 0);
}


// Rule 2: Boids try to keep a small distance away from other objects (including other boids).
FVector UFlockingManager::Rule2(AAgent* boid) {
    FVector repulsionVector = FVector(0, 0, 0);
    float repulsionRadius = 500.0f;

    for (auto other : Agents) {
        if (other != boid) {
            FVector distanceVector = boid->GetActorLocation() - other->GetActorLocation();
            float distance = distanceVector.Size();
            if (distance < repulsionRadius) {
                repulsionVector += distanceVector.GetSafeNormal() * FMath::Square(repulsionRadius - distance) / (distance * distance);
            }
        }
    }

    return repulsionVector;
}

// Rule 3: Boids try to match velocity with near boids.
FVector UFlockingManager::Rule3(AAgent* boid) {
    FVector perceivedVelocity = FVector(0, 0, 0);
    int count = 0;

    for (auto& other : Agents) {
        if (other != boid) {
            perceivedVelocity += other->Velocity;
            count++;
        }
    }

    if (count > 0) {
        perceivedVelocity /= count;
        return (perceivedVelocity - boid->Velocity) / 8.0f;
    }

    return FVector(0, 0, 0);
}


void UFlockingManager::Flock(float DeltaTime) {
    FVector goal = FVector(100.0f, 100.0f, 100.0f); // Example goal location

    for (auto boid : Agents) {
        FVector v1 = Rule1(boid);
        FVector v2 = Rule2(boid);
        FVector v3 = Rule3(boid);
        FVector v4 = StrongWind(boid);
        FVector v5 = TendToPlace(boid, goal);

        boid->Velocity += v1 + v2 + v3 + v4 + v5;
        boid->Velocity = boid->Velocity.GetClampedToMaxSize(MAX_SPEED);

        FVector newLocation = boid->GetActorLocation() + boid->Velocity * DeltaTime;
        boid->SetActorLocation(newLocation);
    }
}

// Example wind vector pushing along the X-axis
FVector UFlockingManager::StrongWind(AAgent* boid) {
    FVector wind = FVector(0.8f, 0.0f, 0.0f);

    // Simulate wind resistance that the faster the boid is moving in the wind's direction, the less effect the wind has
    float windResistance = FMath::Clamp(1.0f - (boid->Velocity.X / MAX_SPEED), 0.0f, 1.0f);
    wind *= windResistance;

    return wind;
}


// Steer each boid towards a particular place
FVector UFlockingManager::TendToPlace(AAgent* boid, const FVector& place) {
    return (place - boid->GetActorLocation()) / 100.0f;
}
