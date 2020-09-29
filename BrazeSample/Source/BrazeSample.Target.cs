// Copyright Braze Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BrazeSampleTarget : TargetRules
{
	public BrazeSampleTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "BrazeSample" } );
	}
}
