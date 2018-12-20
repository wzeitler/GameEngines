// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "RoboConfigFactory.generated.h"

/**
 * 
 */
UCLASS()
class EX5_WALDEMAR_ZEITLER_API URoboConfigFactory : public UFactory
{
	GENERATED_BODY()
	
public:
    // Constructor
    URoboConfigFactory();

private:
    /// Begin UFactor Interface
    // Check if the file can be importet
    virtual bool FactoryCanImport(const FString& Filename) override;
	
	// Create an object from the file
    virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName,
                                        EObjectFlags Flags, const FString& Filename, const TCHAR* Parms,
                                        FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
    /// End UFactor Interface
};
