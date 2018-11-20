// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpeedComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EX1_WZ_API USpeedComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    USpeedComponent();

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
    // Adjustable movment speed
    UPROPERTY(EditAnywhere, Category = "SpeedUp")
        float MovmentSpeed;
    // Adjustable movment speed
    UPROPERTY(EditAnywhere, Category = "SpeedUp")
        float RotationSpeed;

    /** Linear function to calculate the new speed up 
    *   @param current movment speed of the pawn
    *   @return new movment speed of the spawn
    */
    float CalculateMovmentSpeed(float Value);

    /** Linear function to calculate the new rotation rate
    *   @param current rotation rate of the pawn
    *   @return new rotation rate of the spawn
    */
    float CalculateRotationRate(float Value);

private:

    // Values to rest the speed up, to the previous vlaue
    float SpeedUp;
    float RotationUp;

    // Current speed values, for the reset to 0 after movment stops
    float CurrentSpeed;
    float CurrentRotation;
};
