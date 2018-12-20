// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveRobotComponent.h"
#include "EngineUtils.h"

UMoveRobotComponent::UMoveRobotComponent()
{
    FTransform MovmentAndRotation;
    MovmentAndRotation.SetLocation(FVector(0,30,0));
    MovmentAndRotation.SetRotation(FRotator(30,0,0).Quaternion());
    Movment.Add(MovmentAndRotation);
}

// Called when the game starts or when spawned
void UMoveRobotComponent::BeginPlay()
{
    Super::BeginPlay();

    for (TActorIterator<AStaticMeshActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        // Same as with the Object Iterator, access the subclass instance with the * or -> operators.
        AStaticMeshActor *Mesh = *ActorItr;
        UE_LOG(LogTemp, Warning, TEXT("StaticMeshActor: %s"), *ActorItr->GetName());
        if (ActorItr->GetName() == "Projectile")
        {
            Projectile = *ActorItr;
        }
    }  
}

void UMoveRobotComponent::SetMoveableParts(UStaticMeshComponent * BottomPlane, UStaticMeshComponent * Body, UStaticMeshComponent * CanonPart)
{
    MoveableBottomPlane = BottomPlane;
    RobotBody = Body;
    RotateCanon = CanonPart;
}

void UMoveRobotComponent::StartMovment()
{
    MoveableBottomPlane->SetPhysicsAngularVelocityInDegrees(Movment[0].GetRotation().Euler());
    MoveableBottomPlane->SetPhysicsLinearVelocity(Movment[0].GetLocation());
}
