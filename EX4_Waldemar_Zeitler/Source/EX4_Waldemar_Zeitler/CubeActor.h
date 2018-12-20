// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "CubeActor.generated.h"

UCLASS()
class EX4_WALDEMAR_ZEITLER_API ACubeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
    // Box componets, which shall represent the cubes
    UPROPERTY(EditAnywhere, Category = Cube)
        UStaticMeshComponent* FirstBox;
    UPROPERTY(EditAnywhere, Category = Cube)
        UStaticMeshComponent* SecondBox;
    UPROPERTY(EditAnywhere, Category = Cube)
        UStaticMeshComponent* ThirdBox;

private:
    // Set the fitting values for the boxes, to make rotations with constraints possible
    void BoxSetup(UStaticMeshComponent* Box, FVector Scale, FVector RelativePosition);
	
};
