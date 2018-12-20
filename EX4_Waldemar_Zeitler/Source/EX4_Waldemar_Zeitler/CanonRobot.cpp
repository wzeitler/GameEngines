// Fill out your copyright notice in the Description page of Project Settings.

#include "CanonRobot.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
ACanonRobot::ACanonRobot()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // Setup for the three boxes
    BottomPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomPlane"));
    BottomPlane->SetupAttachment(RootComponent);

    Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
    Body->SetupAttachment(RootComponent);

    CanonAttach = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CanonAttach"));
    CanonAttach->SetupAttachment(RootComponent);

    // Find the meshes for the boxes and set them
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (CubeMesh.Succeeded())
    {
        BottomPlane->SetStaticMesh(CubeMesh.Object);
        Body->SetStaticMesh(CubeMesh.Object);
        CanonAttach->SetStaticMesh(CubeMesh.Object);
    }

}

// Called when the game starts or when spawned
void ACanonRobot::BeginPlay()
{
	Super::BeginPlay();
    if (MovmentComponent)
    {
        MovmentComponent->SetMoveableParts(BottomPlane, Body, CanonAttach);
        MovmentComponent->StartMovment();
    }
}

// Called every frame
void ACanonRobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

