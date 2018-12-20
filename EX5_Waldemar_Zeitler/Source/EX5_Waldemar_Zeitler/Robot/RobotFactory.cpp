// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotFactory.h"
#include "Runtime/Engine/Classes/Engine/World.h"

URobotFactory::URobotFactory()
{
    // AActor subclass this ActorFactory creates.
    NewActorClassName = FString("ARModel");
    NewActorClass = ARobot::StaticClass();
}

bool URobotFactory::CanCreateActorFrom(const FAssetData & AssetData, FText & OutErrorMsh)
{
    return AssetData.GetClass()->IsChildOf(URobotConfiguration::StaticClass());
}

AActor * URobotFactory::GetDefaultActor(const FAssetData & AssetData)
{
    return NewActorClass->GetDefaultObject<ARobot>();
}

AActor * URobotFactory::SpawnActor(UObject * Asset, ULevel * InLevel, const FTransform & Transform, 
    EObjectFlags InObjectFlags, const FName Name)
{
    URobotConfiguration* DataAsset = CastChecked<URobotConfiguration>(Asset);
    if (DataAsset)
    {
        ARobot* NewRobot = nullptr;

         AActor* DefaultActor = GetDefaultActor(FAssetData(Asset));
        if (DefaultActor)
        {
             FActorSpawnParameters SpawnInfo;
             SpawnInfo.OverrideLevel = InLevel;
             SpawnInfo.ObjectFlags = InObjectFlags;
             SpawnInfo.Name = FName(Name);

             NewRobot = (ARobot*)InLevel->OwningWorld->SpawnActor(DefaultActor->GetClass(), &Transform, SpawnInfo);
             NewRobot->Load(DataAsset);
        }
        return NewRobot;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Asset vast DataAsset failes"));
    }
    // Creates Robot Actor.
    UE_LOG(LogTemp, Warning, TEXT("No default Robot Actor available\n"));

    return nullptr;
}

void URobotFactory::CreateModels(ARobot * OutModel, URobotConfiguration * InSDFData)
{
}
