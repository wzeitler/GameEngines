// Fill out your copyright notice in the Description page of Project Settings.

#include "SpeedComponent.h"
#include "PlayerPawn.h"

// Sets default values for this component's properties
USpeedComponent::USpeedComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // Pre set values for speed values. 
    // In case the user does not set them in the editor
    MovmentSpeed = 1.0f;
    RotationSpeed = 0.1f;

}

// Called every frame
void USpeedComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Check if the character is still moving. If not reset the CurrentSpeed and SpeedUpTime.
    if (CurrentSpeed != SpeedUp) {
        CurrentSpeed = SpeedUp;
    } 
    else
    {
        SpeedUp = 0;
    }

    if (CurrentRotation != RotationUp)
    {
        CurrentRotation = RotationUp;
    }
    else
    {
        RotationUp = 0;
    }
}

float USpeedComponent::CalculateMovmentSpeed(float Value)
{
    SpeedUp = Value * (MovmentSpeed + FMath::Abs(SpeedUp)); 

    return SpeedUp;
}

float USpeedComponent::CalculateRotationRate(float Value)
{
    RotationUp = Value * (RotationSpeed + FMath::Abs(RotationUp));

    return RotationUp;
}
