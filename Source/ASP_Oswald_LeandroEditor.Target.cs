// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class ASP_Oswald_LeandroEditorTarget : TargetRules
{
	public ASP_Oswald_LeandroEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;

		ExtraModuleNames.AddRange( new string[] { "ASP_Oswald_Leandro" } );
	}
}
