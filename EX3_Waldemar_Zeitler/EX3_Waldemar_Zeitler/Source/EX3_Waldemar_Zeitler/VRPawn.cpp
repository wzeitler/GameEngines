// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    // Can probably be removed
	PrimaryActorTick.bCanEverTick = true;
    
    // Create the root compnent and the camaera
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->AttachTo(RootComponent);

    // Setup for the motion controller hands. Important is the MotionSource, do differentiate the controllers
    LeftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftHand"));
    LeftHand->SetupAttachment(RootComponent);
	LeftHand->MotionSource = FName("Left");
    RightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightHand"));
    RightHand->SetupAttachment(RootComponent);
	RightHand->MotionSource = FName("Right");

    // Get the static controller mesh and set the overlap and physics parameters. 
    // Important to check for overlap events and allow the hands to go through objects
    LeftHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHandStaticMesh"));
    LeftHandMesh->SetupAttachment(LeftHand);
	LeftHandMesh->SetCollisionProfileName("OverlapAllDynamic");
	LeftHandMesh->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftHandMesh->SetEnableGravity(false);
    RightHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHandStaticMesh"));
    RightHandMesh->SetupAttachment(RightHand);
	RightHandMesh->SetCollisionProfileName("OverlapAllDynamic");
	RightHandMesh->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightHandMesh->SetEnableGravity(false);

    // Find the right static mesh of the controller and give it to the hand meshes
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/VREditor/Devices/Vive/VivePreControllerMesh.VivePreControllerMesh'"));
    if (Mesh.Succeeded()) 
    {
        LeftHandMesh->SetStaticMesh(Mesh.Object);
        RightHandMesh->SetStaticMesh(Mesh.Object);
    }


	// Overlap events to check when an object can be picked up
	RightHandMesh->OnComponentBeginOverlap.AddDynamic(this, &AVRPawn::BeginOverlapRight);
	RightHandMesh->OnComponentEndOverlap.AddDynamic(this, &AVRPawn::OnOverlapEndRight);
	LeftHandMesh->OnComponentBeginOverlap.AddDynamic(this, &AVRPawn::BeginOverlapLeft);
	LeftHandMesh->OnComponentEndOverlap.AddDynamic(this, &AVRPawn::OnOverlapEndLeft);

    // Player setup
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Presse and release bindings to the trigger button of the occulus controller
	PlayerInputComponent->BindAction("TakeRight", IE_Pressed, this, &AVRPawn::HoldRight);
	PlayerInputComponent->BindAction("TakeRight", IE_Released, this, &AVRPawn::ThrowRight);
	PlayerInputComponent->BindAction("TakeLeft", IE_Pressed, this, &AVRPawn::HoldLeft);
	PlayerInputComponent->BindAction("TakeLeft", IE_Released, this, &AVRPawn::ThrowLeft);
}

void AVRPawn::BeginOverlapLeft(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    // Save overlaping actor
	if (OverlapActorLeft != OtherActor)
	{
		OverlapActorLeft = OtherActor;
	}
}

void AVRPawn::OnOverlapEndLeft(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
    // Remove overlaping actor
	OverlapActorLeft = nullptr;
}

void AVRPawn::BeginOverlapRight(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    // Save overlaping actor
	if (OverlapActorRight != OtherActor)
	{
		OverlapActorRight = OtherActor;
	}
}

void AVRPawn::OnOverlapEndRight(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
    // Remove overlaping actor
	OverlapActorRight = nullptr;
}

void AVRPawn::HoldRight()
{
    // Attach the overlaping actor to the hand and make him moveable
	if (OverlapActorRight != NULL && RightHandObject == NULL)
	{
        // Cast the OverlapActor to a static mesh actor
		RightHandObject = Cast<AStaticMeshActor>(OverlapActorRight);

		// Physics and gravite need to be romved for the attachment
		RightHandObject->GetStaticMeshComponent()->SetEnableGravity(false);
		RightHandObject->GetStaticMeshComponent()->SetSimulatePhysics(false);
		RightHandObject->AttachToComponent(RightHandMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void AVRPawn::ThrowRight()
{
    // Throw the object out of the hand, when the button is released
	if (RightHandObject != NULL)
	{
		RightHandObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		// Object is detached from the hand and physics can be reset to normal
		RightHandObject->GetStaticMeshComponent()->SetEnableGravity(true);
		RightHandObject->GetStaticMeshComponent()->SetSimulatePhysics(true);
		RightHandObject = nullptr;
	}
}

void AVRPawn::HoldLeft()
{
    // Attach the overlaping actor to the hand and make him moveable
	if (OverlapActorLeft != NULL && LeftHandObject == NULL)
    {
        // Cast the OverlapActor to a static mesh actor
		LeftHandObject = Cast<AStaticMeshActor>(OverlapActorRight);

        // Physics and gravite need to be romved for the attachment
		LeftHandObject->GetStaticMeshComponent()->SetEnableGravity(false);
		LeftHandObject->GetStaticMeshComponent()->SetSimulatePhysics(false);
		LeftHandObject->AttachToComponent(LeftHandMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void AVRPawn::ThrowLeft()
{
    // Throw the object out of the hand, when the button is released
	if (LeftHandObject != NULL)
	{
		LeftHandObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

        // Object is detached from the hand and physics can be reset to normal
		LeftHandObject->GetStaticMeshComponent()->SetEnableGravity(true);
		LeftHandObject->GetStaticMeshComponent()->SetSimulatePhysics(true);
		LeftHandObject = nullptr;
	}
}

