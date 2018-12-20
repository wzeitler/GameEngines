// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "MoveRobotComponent.generated.h"

/**
 * 
 */
UCLASS()
class EX4_WALDEMAR_ZEITLER_API UMoveRobotComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    UMoveRobotComponent();
	
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Get components from robot
    void SetMoveableParts(UStaticMeshComponent* BottomPlane, UStaticMeshComponent* Body, UStaticMeshComponent* CanonPart);

    // Function to start the pre set movment
    void StartMovment();
	
private:
    // The BasePlate from the robot
    UStaticMeshComponent* MoveableBottomPlane;
    // The body from the robot
    UStaticMeshComponent* RobotBody;
    // The CanonPart from the robot
    UStaticMeshComponent* RotateCanon;

    // Projectile to shoot;
    AStaticMeshActor* Projectile;

    // Array with the movments
    TArray<FTransform> Movment;
};
