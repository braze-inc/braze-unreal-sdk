// Copyright Braze Inc. All Rights Reserved.

#include "BrazeModule.h"

#include "BrazeConfig.h"

#include "Developer/Settings/Public/ISettingsModule.h"
#include "Developer/Settings/Public/ISettingsSection.h"

DEFINE_LOG_CATEGORY(LogBraze);

#define LOCTEXT_NAMESPACE "BrazeSDK"

class FBrazeModule : public IBrazeModule
{
	// Begin IModuleInterface
	virtual void StartupModule() final;
	virtual void ShutdownModule() final;
	// End IModuleInterface
};

IMPLEMENT_MODULE(FBrazeModule, Braze)


void FBrazeModule::StartupModule()
{
	UE_LOG(LogBraze, Log, TEXT("Braze plugin startup."));

	// register settings
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingsModule != nullptr)
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "Braze",
			LOCTEXT("BrazeSettingsName", "Braze SDK"),
			LOCTEXT("BrazeSettingsDescription", "Configure the Braze SDK plug-in."),
			GetMutableDefault<UBrazeConfig>()
		);
	}
}

void FBrazeModule::ShutdownModule()
{
	UE_LOG(LogBraze, Log, TEXT("Braze plugin shutdown."));

	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingsModule != nullptr)
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Braze");
	}
}

#undef LOCTEXT_NAMESAPCE
