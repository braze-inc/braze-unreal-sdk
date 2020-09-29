// Copyright Braze Inc. All Rights Reserved.

using UnrealBuildTool;

public class BrazeSample : ModuleRules
{
	public BrazeSample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Braze" });

		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
