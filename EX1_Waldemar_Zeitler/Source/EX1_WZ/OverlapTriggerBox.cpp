// Fill out your copyright notice in the Description page of Project Settings.

#include "OverlapTriggerBox.h"
#include "DrawDebugHelpers.h"
#include "ScaleActor.h"
#include "EngineUtils.h"

AOverlapTriggerBox::AOverlapTriggerBox()
{
    //Register Events
    OnActorBeginOverlap.AddDynamic(this, &AOverlapTriggerBox::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &AOverlapTriggerBox::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AOverlapTriggerBox::BeginPlay()
{
    Super::BeginPlay();

    DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);

    //Iterate over all objects in the world and the the scale actor
    for (TActorIterator<AScaleActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
        ScaleActor = *ActorItr;
    }
}

void AOverlapTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    // check if Actors do not equal nullptr and that 
    if (OtherActor && (OtherActor != this)) {
        // print to screen using above defined method when actor enters trigger box
        UE_LOG(LogTemp, Log, TEXT("Overlap Begin"));
        UE_LOG(LogTemp, Log, TEXT("Overlapped Actor = %s"), *OtherActor->GetName());

        if (ScaleActor != NULL)
        {
            ScaleActor->bTriggered = true;
        }
    }
}

void AOverlapTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
    if (OtherActor && (OtherActor != this)) {
        // print to screen using above defined method when actor leaves trigger box
        UE_LOG(LogTemp, Log, TEXT("Overlap Ended"));
        UE_LOG(LogTemp, Log, TEXT("%s has left the Trigger Box"), *OtherActor->GetName());
    }
}
