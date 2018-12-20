// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeActor.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
ACubeActor::ACubeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // Setup for the three boxes
    FirstBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstBox"));
    BoxSetup(FirstBox, FVector(0.8, 0.8, 0.8), FVector::ZeroVector);

    SecondBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondBox"));
    BoxSetup(SecondBox, FVector(0.5, 0.5, 0.5), FVector(40, 40, 0));

    ThirdBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThirdBox"));
    BoxSetup(ThirdBox, FVector(0.3, 0.3, 0.3), FVector(80, 80, 0));

    // Find the meshes for the boxes and set them
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (CubeMesh.Succeeded())
    {
        FirstBox->SetStaticMesh(CubeMesh.Object);
        SecondBox->SetStaticMesh(CubeMesh.Object);
        ThirdBox->SetStaticMesh(CubeMesh.Object);
    }
}

void ACubeActor::BoxSetup(UStaticMeshComponent* Box, FVector Scale, FVector RelativePosition)
{
    // Box settings for the rotation with constraints
    Box->SetupAttachment(RootComponent);
    Box->SetWorldScale3D(Scale);
    Box->SetRelativeLocation(RelativePosition);
    Box->SetSimulatePhysics(true);
    Box->SetEnableGravity(false);
}

// Called when the game starts or when spawned
void ACubeActor::BeginPlay()
{
	Super::BeginPlay();

    float ThirdCubeRotation = 360 / 2.4f;

    // With -320 the cube needs around 10 seconds to orbit the first box
    SecondBox->SetPhysicsLinearVelocity(FVector(0, -320, 0));
    SecondBox->SetPhysicsAngularVelocityInDegrees(FVector(0, 0, ThirdCubeRotation));

    //ThirdBox->SetPhysicsLinearVelocity(FVector(0, -720, 0));
    ThirdBox->SetPhysicsAngularVelocityInDegrees(FVector(0, 0, ThirdCubeRotation));
}
