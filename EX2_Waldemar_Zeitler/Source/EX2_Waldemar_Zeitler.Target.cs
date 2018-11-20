// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class EX2_Waldemar_ZeitlerTarget : TargetRules
{
	public EX2_Waldemar_ZeitlerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("EX2_Waldemar_Zeitler");
	}
}
