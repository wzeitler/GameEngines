// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class EX5_Waldemar_ZeitlerTarget : TargetRules
{
	public EX5_Waldemar_ZeitlerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "EX5_Waldemar_Zeitler" } );
	}
}
