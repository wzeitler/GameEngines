// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class EX3_Waldemar_ZeitlerTarget : TargetRules
{
	public EX3_Waldemar_ZeitlerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("EX3_Waldemar_Zeitler");
	}
}
