// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RobotConfiguration.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Core/Public/Containers/Set.h"
#include "Robot.generated.h"

UCLASS()
class EX5_WALDEMAR_ZEITLER_API ARobot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARobot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void Load(URobotConfiguration* Model);

private:
    // Functions to load the links and joints in
    void LoadLinks(const FLink& RobotLink);
    void LoadJoints(const FJoints& RobotJoins);

    // Member variables
    UPROPERTY(EditAnywhere)
        TMap<FString, UStaticMeshComponent*> Links;
    UPROPERTY(EditAnywhere)
        TMap<FString, UPhysicsConstraintComponent*> Joints;

    // Robot parts
    UStaticMesh* Box;
    UStaticMesh* Cylinder;

    // Test example with the seperate components
    UCapsuleComponent* CylinderComponent;
    UBoxComponent* BoxComponent;
};
