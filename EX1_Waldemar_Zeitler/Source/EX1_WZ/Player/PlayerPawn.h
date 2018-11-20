// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

// Forward declaration for the speed component
class USpeedComponent;

UCLASS()
class EX1_WZ_API APlayerPawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    APlayerPawn();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    /** Bluprint function to finde the actors in front of the pawn
    *   @return The list of the found actors
    */
    UFUNCTION(BlueprintImplementableEvent, Category = "ActorFinding")
        TArray<FHitResult> GetActorList();

private:
    // Rotation of the character
    void AddPitchInput(float Value);
    void AddYawInput(float Value);

    // Movment of the cahracter
    void AddStraightMovment(float Value);
    void AddSideMovment(float Value);
    
    // Calculate new speed velocity
    float CalculateNewVelocity(float Value);

    // Function bound to the action button "E", 
    // to start finding actors in fornt of the pawn.
    void FindActors();

    // Adjustable rotation speed of pawn
    float RotationRate;

    // Adjustable movment speed of pawn
    float MovmentSpeed;

    // Component to handle the linear speed up or rotation and movment
    USpeedComponent* SpeedComponent;

    // Last location of the pawn after the movment, to rest the speed up
    FVector LastLocation;

    // Last rotation of the pawn after rotating, to rest the rotation
    FRotator LastRotation;
};
