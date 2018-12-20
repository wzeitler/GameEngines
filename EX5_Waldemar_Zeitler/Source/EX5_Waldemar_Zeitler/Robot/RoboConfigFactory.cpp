// Fill out your copyright notice in the Description page of Project Settings.

#include "RoboConfigFactory.h"
#include "RobotConfiguration.h"
#include "Editor/UnrealEd/Public/Editor.h"
#include "Parser.h"

URoboConfigFactory::URoboConfigFactory()
{
    // Which asset type can the factory import
    SupportedClass = URobotConfiguration::StaticClass();

    // List of supported formats. Each entry is of the form "ext;Description" where
    // ext is the file extension
    Formats.Add(TEXT("urdf;URDF robot description format"));

    // Factory imports objects from files
    bEditorImport = true;

    // Required the spesific other reimports do their CanReimport checks first
    ImportPriority = DefaultImportPriority - 1;
}

bool URoboConfigFactory::FactoryCanImport(const FString & Filename)
{
    return Filename.EndsWith(".urdf", ESearchCase::IgnoreCase);
}

UObject * URoboConfigFactory::FactoryCreateFile(UClass * InClass, UObject * InParent, FName InName, EObjectFlags Flags, 
    const FString & Filename, const TCHAR * Parms, FFeedbackContext * Warn, bool & bOutOperationCanceled)
{
    UE_LOG(LogTemp, Log, TEXT("InName %s, InParentName %s"), *InName.ToString(), *InParent->GetName());

    Flags |= RF_Transactional;

    // Called when new assets are being (re-)imported
    FEditorDelegates::OnAssetPreImport.Broadcast(this, InClass, InParent, InName, Parms);

    // Parse the .sdf buffer data into the data asset
    Parser SdfParser(Filename);

    // Create a new DataAsset
    URobotConfiguration* NewDataAsset = SdfParser.ParseToNewDataAsset(InParent, InName, Flags);

    // Called when new assets have been (re-)imported
    FEditorDelegates::OnAssetPostImport.Broadcast(this, NewDataAsset);

    return NewDataAsset;
}
