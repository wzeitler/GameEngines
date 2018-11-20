// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Curves/CurveFloat.h"
#include "GameFramework/Actor.h"
#include "ScaleActor.generated.h"

UCLASS()
class EX1_WZ_API AScaleActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AScaleActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Mesh component to hold the static mesh
    UPROPERTY(EditAnywhere, Category = Mesh)
        UStaticMeshComponent* MeshComp;

    UPROPERTY(EditDefaultsOnly, Category = Curve)
        UCurveFloat* Curve;

    // Scale and rotation parameters for the object.
    // Are set in begin play of the blueprint
    UPROPERTY(BlueprintReadWrite)
        float ScaleFaktor;
    UPROPERTY(BlueprintReadWrite)
        float RotateValue;
    UPROPERTY(BlueprintReadWrite)
        bool bScaleUp;

    // Start scaling and rotating, because the player is in the trigger box
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        bool bTriggered;
private:

    /** Scales and rotates the actor, according to the parameters and the float curve
    *   @param seconds to access the curve values
    */
    UFUNCTION(BlueprintCallable)
        void ScaleRotate(float DeltaSeconds);

    // Curve time values
    float MinCurveTime;
    float MaxCurveTime;
};
