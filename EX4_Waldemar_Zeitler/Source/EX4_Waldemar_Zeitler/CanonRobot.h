// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "MoveRobotComponent.h"
#include "CanonRobot.generated.h"

UCLASS()
class EX4_WALDEMAR_ZEITLER_API ACanonRobot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACanonRobot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
    // Box componets, which shall represent the cubes
    UPROPERTY(EditAnywhere, Category = Box)
        UStaticMeshComponent* BottomPlane;
    UPROPERTY(EditAnywhere, Category = Box)
        UStaticMeshComponent* Body;
    UPROPERTY(EditAnywhere, Category = Box)
        UStaticMeshComponent* CanonAttach;

private:
    // UStaticMeshCOmponent for the movment
    UPROPERTY(EditAnywhere)
        UMoveRobotComponent* MovmentComponent;
};
