// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/XmlParser/Public/XmlFile.h"
#include "RobotConfiguration.h"

/**
 * 
 */
class EX5_WALDEMAR_ZEITLER_API Parser
{

public:
	Parser(const FString& Filename);
	~Parser();

    URobotConfiguration* ParseToNewDataAsset(UObject * InParent, FName InName, EObjectFlags Flags);

protected:
    // Data asset object
    URobotConfiguration* DataAsset;

    // The loaded urdf
    FXmlFile* XmlFile;

private:
    // Functions to parse the links and joints of the urdf file
    FLink ParseLink(const FString& Name, const FXmlNode* LinkNode);
    FJoints ParseJoint(const FString& Name, const FXmlNode* JointNode);
};
