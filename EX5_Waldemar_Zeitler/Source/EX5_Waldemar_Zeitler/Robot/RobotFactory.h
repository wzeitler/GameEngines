// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorFactories/ActorFactory.h"
#include "RobotConfiguration.h"
#include "Runtime/AssetRegistry/Public/AssetData.h"
#include "Robot.h"
#include "RobotFactory.generated.h"

/**
 * 
 */
UCLASS()
class EX5_WALDEMAR_ZEITLER_API URobotFactory : public UActorFactory
{
	GENERATED_BODY()
	
private:
    // Constructor
    URobotFactory();
	
#if WITH_EDITOR

    virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsh) override;

    /** Initialize NewActorClass if necessary, and retur default actor for that class. */
    virtual AActor* GetDefaultActor(const FAssetData& AssetData) override;

    /** Spawns the robot */
    virtual AActor* SpawnActor(UObject* Asset, ULevel* InLevel, const FTransform& Transform,
                                EObjectFlags InObjectFlags, const FName Name) override;

    virtual void CreateModels(ARobot* OutModel, URobotConfiguration* InSDFData);

#endif
	
};
