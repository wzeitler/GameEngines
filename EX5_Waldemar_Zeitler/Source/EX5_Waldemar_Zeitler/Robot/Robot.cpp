// Fill out your copyright notice in the Description page of Project Settings.

#include "Robot.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
ARobot::ARobot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

    // Find the meshes for the boxes and set them
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (CubeMesh.Succeeded())
    {
        Box = CubeMesh.Object;
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("StaticMesh'/Engine/EngineMeshes/Cylinder.Cylinder'"));
    if (CylinderMesh.Succeeded())
    {
        Cylinder = CylinderMesh.Object;
    }

}

// Called when the game starts or when spawned
void ARobot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARobot::Load(URobotConfiguration * Model)
{
    for (const auto& Link : Model->Links)
    {
        LoadLinks(Link);
    }
    
    for (const auto& Joint : Model->Joints)
    {
        LoadJoints(Joint);
    }
}

void ARobot::LoadLinks(const FLink& RobotLink)
{
    FString Name = RobotLink.Name;

    UStaticMeshComponent* Link = NewObject<UStaticMeshComponent>(this);
    Link->SetupAttachment(RootComponent);

    if (RobotLink.Form.Contains("box"))
    {
        /**
        BoxComponent = NewObject<UBoxComponent>();;
        BoxComponent->SetWorldTransform(RobotLink.Pose);
        BoxComponent->SetWorldScale3D(RobotLink.Size);
        BoxComponent->AttachTo(Link);
        */

        Link->SetStaticMesh(Box);
        Link->SetRelativeTransform(RobotLink.Pose);
        Link->SetWorldScale3D(RobotLink.Size);   
    }

    if (RobotLink.Form.Contains("Cylinder"))
    {
        /**
        UCapsuleComponent* CylinderLink = NewObject<UCapsuleComponent>();
        CylinderLink->SetCapsuleRadius(RobotLink.Radius);
        CylinderLink->SetCapsuleHalfHeight(RobotLink.Length / 2);
        CylinderLink->SetWorldTransform(RobotLink.Pose);
        CylinderLink->AttachTo(Link);
        */
        Link->SetRelativeTransform(RobotLink.Pose);
        Link->SetStaticMesh(Cylinder);
    }

    Links.Add(Name, Link);
}

void ARobot::LoadJoints(const FJoints& RobotJoins)
{
    FConstraintInstance ConstraintInstance;

    FString Name = RobotJoins.Name;
    UStaticMeshComponent* Parent = Links[RobotJoins.Parent];
    UStaticMeshComponent* Child = Links[RobotJoins.Child];

    UPhysicsConstraintComponent* Joint = NewObject<UPhysicsConstraintComponent>(this);

    Joint->AttachToComponent(Parent, FAttachmentTransformRules::KeepWorldTransform);

    //Set World Location
    Joint->SetRelativeTransform(RobotJoins.Pose);

    //~~~ Init Constraint ~~~
    Joint->SetConstrainedComponents(Parent, NAME_None, Child, NAME_None);

    Joint->SetAngularOrientationTarget(RobotJoins.Axis.Rotation());

    Joints.Add(Name, Joint);
}

