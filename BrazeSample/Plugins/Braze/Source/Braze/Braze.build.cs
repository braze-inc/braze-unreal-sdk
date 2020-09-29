// Copyright Braze Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Braze : ModuleRules
{
	public Braze(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDefinitions.Add("BRAZE_PACKAGE=1");
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
		PrivateDependencyModuleNames.AddRange(new string[] { });

        // Android Specific
        if (Target.Platform == UnrealTargetPlatform.Android)
        {
			// For AndroidJNI
			PublicIncludePathModuleNames.Add("Launch");
			PrivateDependencyModuleNames.AddRange(new string[] { "Launch", });

			// Must be named AndroidPlugin
			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "BrazeUPLAndroid.xml"));
		}

        // IOS specific
        if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			PublicFrameworks.AddRange(new string[] { "AdSupport", "CoreTelephony" });
            
			string FrameworkPath = Path.Combine(ModuleDirectory, "../ThirdParty/IOS/");
			PublicAdditionalLibraries.Add(Path.Combine(FrameworkPath, "libBrazeIOS.a"));
            
			// todo: Attempt a static framework, use the following:
			// PublicAdditionalFrameworks.Add(new Framework("Appboy_IOS_SDK", Path.Combine(FrameworkPath, "Appboy_IOS_SDK.framework.zip")));
			// RuntimeDependencies.Add(Path.Combine(FrameworkPath, "Appboy_IOS_SDK.framework.zip"));
		}
    }
}
