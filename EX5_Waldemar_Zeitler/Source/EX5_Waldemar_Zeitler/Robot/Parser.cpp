// Fill out your copyright notice in the Description page of Project Settings.

#include "Parser.h"

Parser::Parser(const FString& Filename)
{
    XmlFile = new FXmlFile(Filename, EConstructMethod::ConstructFromFile); 
}

Parser::~Parser()
{
}

URobotConfiguration * Parser::ParseToNewDataAsset(UObject * InParent, FName InName, EObjectFlags Flags)
{
    DataAsset = NewObject<URobotConfiguration>(InParent, InName, Flags);

    for (const auto& ChildNode : XmlFile->GetRootNode()->GetChildrenNodes())
    {
        FString Tag = ChildNode->GetTag();
        FString NameAttribute = ChildNode->GetAttribute(TEXT("name"));

        if (Tag.Contains(FString("link")))
        {
            DataAsset->Links.Add(ParseLink(NameAttribute, ChildNode));
        }

        if (Tag.Contains(FString("joint")))
        {
            DataAsset->Joints.Add(ParseJoint(NameAttribute, ChildNode));
        }
    }

    return DataAsset;
}

FLink Parser::ParseLink(const FString & Name, const FXmlNode * LinkNode)
{
    FLink RobotLink;
    RobotLink.Name = Name;
    UE_LOG(LogTemp, Warning, TEXT("Link Name: /%s"), *Name);

    // Go through the elements of the child nodes
    for (const auto& ChildAttributes : LinkNode->GetChildrenNodes())
    {
        FString Attribute = ChildAttributes->GetTag();
        if (Attribute.Contains("pose"))
        {
            FString Content = ChildAttributes->GetContent();
            TArray<FString> Parts;
            Content.ParseIntoArrayWS(Parts);

            FVector Origin;
            Origin.X = FCString::Atof(*Parts[0]);
            Origin.Y = FCString::Atof(*Parts[1]);
            Origin.Z = FCString::Atof(*Parts[2]);

            FRotator Rotation;
            Rotation.Roll = FCString::Atof(*Parts[3]);
            Rotation.Pitch = FCString::Atof(*Parts[4]);
            Rotation.Yaw = FCString::Atof(*Parts[5]);

            RobotLink.Pose.SetLocation(Origin);
            RobotLink.Pose.SetRotation(Rotation.Quaternion());
        }
        if (Attribute.Contains("geometry"))
        {
            //UE_LOG(LogTemp, Warning, TEXT("Box Tag: %s \n"), *ChildAttributes->GetFirstChildNode()->GetTag());
            RobotLink.Form = ChildAttributes->GetFirstChildNode()->GetTag();


            if (RobotLink.Form.Contains("box"))
            {
                const FXmlNode* Size = ChildAttributes->GetFirstChildNode()->GetFirstChildNode();
                //UE_LOG(LogTemp, Warning, TEXT("Size Content: %s \n"), *Size->GetContent());

                FString Content = Size->GetContent();
                TArray<FString> Parts;
                Content.ParseIntoArrayWS(Parts);

                FVector SizeVector;
                SizeVector.X = FCString::Atof(*Parts[0]);
                SizeVector.Y = FCString::Atof(*Parts[1]);
                SizeVector.Z = FCString::Atof(*Parts[2]);

                RobotLink.Size = SizeVector;
            }
            if (RobotLink.Form.Contains("cylinder"))
            {
                // The cylinder is parsed like the box, because their is no example in the urdf.
                // The example from http://wiki.ros.org/urdf/XML/link looks diferent but assuming 
                // that box and cylinder have the same syntax the following implementation was choosen.
                for (const auto& CylinderChild : ChildAttributes->GetFirstChildNode()->GetChildrenNodes())
                {
                    FString Parameter = CylinderChild->GetTag();
                    if (Parameter.Contains("radius"))
                    {
                        FString Radius = CylinderChild->GetContent();
                        RobotLink.Radius = FCString::Atof(*Radius);

                    }
                    if (Parameter.Contains("length"))
                    {
                        FString Length = CylinderChild->GetContent();
                        RobotLink.Length = FCString::Atof(*Length);
                    }
                }
            }

        }

    }
    return RobotLink;
}

FJoints Parser::ParseJoint(const FString & Name, const FXmlNode * JointNode)
{
    FJoints RobotJoints;
    RobotJoints.Name = Name;
    UE_LOG(LogTemp, Warning, TEXT("Joint Name: /%s"), *Name);
    RobotJoints.Type = JointNode->GetAttribute("type");

    for (const auto& ChildAttributes : JointNode->GetChildrenNodes())
    {
        //UE_LOG(LogTemp, Warning, TEXT("Joint Child Tag: %s \n"), *ChildAttributes->GetTag());
        //UE_LOG(LogTemp, Warning, TEXT("Joint Child Content: %s \n"), *ChildAttributes->GetContent());

        FString ChildTag = ChildAttributes->GetTag();
        if (ChildTag.Contains("pose"))
        {
            FString Content = ChildAttributes->GetContent();
            TArray<FString> Parts;
            Content.ParseIntoArrayWS(Parts);

            FVector Origin;
            Origin.X = FCString::Atof(*Parts[0]);
            Origin.Y = FCString::Atof(*Parts[1]);
            Origin.Z = FCString::Atof(*Parts[2]);

            RobotJoints.Pose.SetLocation(Origin);
        }
        if (ChildTag.Contains("parent"))
        {
            UE_LOG(LogTemp, Warning, TEXT("Joint Parent: /%s"), *ChildAttributes->GetContent());
            RobotJoints.Parent = ChildAttributes->GetContent();
        }
        if (ChildTag.Contains("child"))
        {
            UE_LOG(LogTemp, Warning, TEXT("Joint Child: /%s"), *ChildAttributes->GetContent());
            RobotJoints.Child = ChildAttributes->GetContent();
        }
        if (ChildTag.Contains("axis"))
        {
            const FXmlNode* Axis = ChildAttributes->GetFirstChildNode();

            FString Content = Axis->GetContent();
            TArray<FString> Parts;
            Content.ParseIntoArrayWS(Parts);

            FVector AxisVector;
            AxisVector.X = FCString::Atof(*Parts[0]);
            AxisVector.Y = FCString::Atof(*Parts[1]);
            AxisVector.Z = FCString::Atof(*Parts[2]);

            RobotJoints.Axis = AxisVector;
        }
      
    }
    return RobotJoints;
}
