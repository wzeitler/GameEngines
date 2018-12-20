// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class EX4_Waldemar_ZeitlerTarget : TargetRules
{
	public EX4_Waldemar_ZeitlerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "EX4_Waldemar_Zeitler" } );
	}
}
