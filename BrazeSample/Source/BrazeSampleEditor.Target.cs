// Copyright Braze Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BrazeSampleEditorTarget : TargetRules
{
	public BrazeSampleEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "BrazeSample" } );
	}
}
