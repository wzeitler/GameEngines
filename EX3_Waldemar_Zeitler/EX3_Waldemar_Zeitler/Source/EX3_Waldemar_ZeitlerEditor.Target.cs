// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class EX3_Waldemar_ZeitlerEditorTarget : TargetRules
{
	public EX3_Waldemar_ZeitlerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("EX3_Waldemar_Zeitler");
	}
}
