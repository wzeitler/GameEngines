// Fill out your copyright notice in the Description page of Project Settings.

#include "CraneActor.h"
#include "EngineUtils.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
ACraneActor::ACraneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // Setup for the three boxes
    BottomPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomPlane"));
    BottomPlane->SetupAttachment(RootComponent);

    Arm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
    Arm->SetupAttachment(RootComponent);

    Gripper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CanonAttach"));
    Gripper->SetupAttachment(RootComponent);

    // Find the meshes for the boxes and set them
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (CubeMesh.Succeeded())
    {
        BottomPlane->SetStaticMesh(CubeMesh.Object);
        Arm->SetStaticMesh(CubeMesh.Object);
        Gripper->SetStaticMesh(CubeMesh.Object);
    }

    // Overlap events to check when an object can be picked up
    Gripper->OnComponentBeginOverlap.AddDynamic(this, &ACraneActor::BeginOverlap);
    Gripper->OnComponentEndOverlap.AddDynamic(this, &ACraneActor::OnOverlapEnd);

    Rotated = 0;
    bDetached = false;
}

// Called when the game starts or when spawned
void ACraneActor::BeginPlay()
{
	Super::BeginPlay();

    for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        if (ActorItr->GetName().Contains("MoveableObject"))
        {
            ObjectPosition = ActorItr->GetActorLocation();
        }
    }

    DropPosition = ObjectPosition + FVector(-220, 0, 0);

    StartPosition = this->GetActorLocation();
}

// Called every frame
void ACraneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!bAttached)
    {
        MoveToPickupPosition();
    }
    else if (!bDetached)
    {
        MoveToDropPosition();
    }
    if (bDetached)
    {
        AttachedObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        bReturn = true;
    }
    if (bReturn)
    {
        ReturnToOrigin();
    }
}

void ACraneActor::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if (!bAttached)
    {
        // Check if the right object is overlapping
        if (OtherActor->GetName().Contains("MoveableObject"))
        {
            AttachedObject = OtherActor;
            AttachedObject->AttachToComponent(Gripper, FAttachmentTransformRules::KeepWorldTransform);
            bAttached = true;
        }
    }
}

void ACraneActor::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
    
}

void ACraneActor::MoveToPickupPosition()
{
    if (ObjectPosition.X < this->GetActorLocation().X)
    {
        AddActorWorldOffset(FVector(-1, 0, 0));
    }
    else if (ObjectPosition.X > this->GetActorLocation().X)
    {
        AddActorWorldOffset(FVector(1, 0, 0));
    }
    else if (ObjectPosition.Y < this->GetActorLocation().Y)
    {
        AddActorWorldOffset(FVector(0, -1, 0));
    }
    else if (ObjectPosition.Y > this->GetActorLocation().Y)
    {
        AddActorWorldOffset(FVector(0, 1, 0));
    }
}

void ACraneActor::MoveToDropPosition()
{
    if (Rotated < 90)
    {
        AddActorWorldRotation(FRotator(0, 1, 0));
        Rotated++;
    }
    else
    {
        if (DropPosition.X < this->GetActorLocation().X)
        {
            AddActorWorldOffset(FVector(-1, 0, 0));
        }
        else if (DropPosition.X > this->GetActorLocation().X)
        {
            AddActorWorldOffset(FVector(1, 0, 0));
        }
        else if (DropPosition.Y < this->GetActorLocation().Y)
        {
            AddActorWorldOffset(FVector(0, -1, 0));
        }
        else if (DropPosition.Y > this->GetActorLocation().Y)
        {
            AddActorWorldOffset(FVector(0, 1, 0));
        }
        else
        {
            bDetached = true;
        }
    }
}

void ACraneActor::ReturnToOrigin()
{
    if (Rotated != 0)
    {
        AddActorWorldRotation(FRotator(0, -1, 0));
        Rotated--;
    }
    else
    {
        if (StartPosition.X < this->GetActorLocation().X)
        {
            AddActorWorldOffset(FVector(-1, 0, 0));
        }
        else if (StartPosition.X > this->GetActorLocation().X)
        {
            AddActorWorldOffset(FVector(1, 0, 0));
        }
        else if (StartPosition.Y < this->GetActorLocation().Y)
        {
            AddActorWorldOffset(FVector(0, -1, 0));
        }
        else if (StartPosition.Y > this->GetActorLocation().Y)
        {
            AddActorWorldOffset(FVector(0, 1, 0));
        }
    }
}