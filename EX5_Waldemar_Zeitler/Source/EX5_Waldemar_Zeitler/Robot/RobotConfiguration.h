// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RobotConfiguration.generated.h"


// Struct for the links
USTRUCT()
struct FLink
{
    GENERATED_BODY()

public:

    // FLink variables
    FString Name;
    FString Form;
    FTransform Pose;
    FVector Size;
    float Radius;
    float Length;

    //Constructor
    FLink()
    {
        // pre initialize variables
        Name = FString("");
        Form = FString("");
        Pose = FTransform();
        Size = FVector::ZeroVector;
        Radius = 0.0f;
        Length = 0.0f;
    }
};

// Struct for the joints
USTRUCT()
struct FJoints
{
    GENERATED_BODY()

public:

    // FJoint variables
    FString Name;
    FString Type;
    FTransform Pose;
    FVector Axis;
    FString Parent;
    FString Child;

    //Constructor
    FJoints()
    {
        // pre initialize variables
        Name = FString("");
        Type = FString("");
        Pose = FTransform();
        Axis = FVector::ZeroVector;
        Parent = FString("");
        Child = FString("");
    }
};

/**
 * Main Configuration class
 */
UCLASS()
class EX5_WALDEMAR_ZEITLER_API URobotConfiguration : public UDataAsset
{
	GENERATED_BODY()
	
	
public:
    // Member struct FLink
    TArray<FLink> Links;
    // Member struct FJoint
    TArray<FJoints> Joints;
	
};
