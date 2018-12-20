// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "CraneActor.generated.h"

UCLASS()
class EX5_WALDEMAR_ZEITLER_API ACraneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACraneActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
    // Box componets, which shall represent the cubes
    UPROPERTY(EditAnywhere, Category = Body)
        UStaticMeshComponent* BottomPlane;
    UPROPERTY(EditAnywhere, Category = Body)
        UStaticMeshComponent* Arm;
    UPROPERTY(EditAnywhere, Category = Body)
        UStaticMeshComponent* Gripper;
	
private:
    // Overlap begin and end functions for the left hand
    UFUNCTION()
        void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
    UFUNCTION()
        void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    // Oevalp actor to move
    UPROPERTY()
        AActor* AttachedObject;

    // Position of the object to pick up
    UPROPERTY(VisibleAnywhere)
        FVector ObjectPosition;
    // Position to detach the object
    UPROPERTY(VisibleAnywhere)
        FVector DropPosition;

    // Default Pose
    UPROPERTY(VisibleAnywhere)
        FVector StartPosition;

    // Functions to move the actor
    void MoveToPickupPosition();
    void MoveToDropPosition();
    void ReturnToOrigin();

    // Bools to check the current state of the roboter
    bool bAttached;
    bool bDetached;
    bool bReturn;

    // Rotation check of the actor
    int Rotated;
};
