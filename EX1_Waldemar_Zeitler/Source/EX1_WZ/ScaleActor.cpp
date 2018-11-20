// Fill out your copyright notice in the Description page of Project Settings.

#include "ScaleActor.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ConstructorHelpers.h"

// Sets default values
AScaleActor::AScaleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScaleMesh"));

    // Pre set parameters for scaling
    ScaleFaktor = 0.1;
    RotateValue = 5;
    bScaleUp = true;
}

// Called when the game starts or when spawned
void AScaleActor::BeginPlay()
{
	Super::BeginPlay(); 

    // If a curve was given get the min and max time of the curve
    if (Curve)
    {
        Curve->GetTimeRange(MinCurveTime, MaxCurveTime);
    }
    
}

// Called every frame
void AScaleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AScaleActor::ScaleRotate(float DeltaSeconds)
{
    // Rise the min time value of the curve, until the max time is reached, to stop the "animation"
    if (MinCurveTime < MaxCurveTime)
    {
        // Calculate the new rotation
        float Rotation = RotateValue * Curve->GetFloatValue(MinCurveTime);
        FQuat NewRotation = FQuat(FRotator(Rotation, 0.f, 0.f));
        AddActorWorldRotation(NewRotation);

        // Calculate the scaling, depending if the object should get smaller or bigger
        float Scaling = ScaleFaktor * Curve->GetFloatValue(MinCurveTime);
        if (!bScaleUp && Scaling > 0)
        {
            Scaling = Scaling * -1;
        }

        FVector RisingScale = GetActorScale();
        RisingScale += FVector(Scaling, Scaling, Scaling);

        SetActorScale3D(RisingScale);

        MinCurveTime += DeltaSeconds;
    }
    else
    {
        // Rest the time values and deactived the trigger
        Curve->GetTimeRange(MinCurveTime, MaxCurveTime);
        bTriggered = false;
    }
}
