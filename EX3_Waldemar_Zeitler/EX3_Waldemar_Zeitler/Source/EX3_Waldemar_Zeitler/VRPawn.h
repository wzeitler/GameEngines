// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Runtime/HeadMountedDisplay/Public/MotionControllerComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "VRPawn.generated.h"

UCLASS()
class EX3_WALDEMAR_ZEITLER_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Hand components for the motion controllers
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Controller)
        UMotionControllerComponent* LeftHand;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Controller)
        UMotionControllerComponent* RightHand;
	
    // Static meshe components of the motion controller, for visual feedback
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Controller)
        UStaticMeshComponent* LeftHandMesh;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Controller)
        UStaticMeshComponent* RightHandMesh;

private:
	// Overlaped actor
	AActor* OverlapActorLeft;
	AActor* OverlapActorRight;

    // MeshActors which are attached to the hands during the overlap event and button press
	AStaticMeshActor* RightHandObject;
	AStaticMeshActor* LeftHandObject;

	// Overlap begin and end functions for the left hand
	UFUNCTION()
		void BeginOverlapLeft(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void OnOverlapEndLeft(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    // Overlap begin and end functions for the right hand
	UFUNCTION()
		void BeginOverlapRight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void OnOverlapEndRight(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    // Button press and release functions of the right hand
	UFUNCTION()
		void HoldRight();
	UFUNCTION()
		void ThrowRight();

    // Button press and release functions of the left hand
	UFUNCTION()
		void HoldLeft();
	UFUNCTION()
		void ThrowLeft();

};
