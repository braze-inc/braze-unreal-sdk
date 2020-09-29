// Copyright Braze Inc. All Rights Reserved.

#pragma once

#include "Braze.h"
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BrazeSubsystem.generated.h"

class UBrazeConfig;

/**
 * LogLevel matching the android.util.log priority constants as well as AppboyLogger.Suppress
 */
UENUM(BlueprintType)
enum class EBrazeLogLevel : uint8 {
	Invalid = 0,
	Verbose = 2,
	Debug = 3,
	Info = 4,
	Warn = 5,
	Error = 6,
	Assert = 7,
	Suppress = 255,
};

UCLASS(BlueprintType, ClassGroup=Braze)
class BRAZE_API UBrazeSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/**
	 * Initialize the Braze Instance manually, optionally pass a config, or else, use the default config based on ini settings
	 * 
	 * @param Config (Optional) A config Object with ApiKeys and Custom Endpoint filled out if necessary. Will use the Default object set from ini if not passed
	 * @return Initialized instance of UBraze
	 */
	UFUNCTION(BlueprintCallable)
	UBraze* InitializeBraze(const UBrazeConfig* Config = nullptr);

	/**
	 * @return the current BrazeInstance
	 */
	UBraze* GetBrazeInstance() const { return BrazeInstance; }

	/**
	 * On Android only, set the Logging Level. 
	 * This is best called before InitializeBraze
	 *
	 * NOTE: To set the log level for iOS, you must do so through the info.plist.
	 * In Project Settings, in the "Additional Plist Data" field of the iOS settings category
	 * Add the following:
	 * <key>Appboy</key>
	 * <dict>
	 *   <key>LogLevel</key>
	 *   <string>0</string>
	 * </dict>
	 * The default log level is 8, which is minimal logging. See README.md for more information.
	 * @param BrazeLogLevel
	 */
	UFUNCTION(BlueprintCallable)
	void AndroidSetLogLevel(EBrazeLogLevel BrazeLogLevel = EBrazeLogLevel::Info);
	
	/**
	 * Enables the Braze SDK after an invocation of DisableSDK. Note that the Braze SDK is enabled by default.
	 * All network requests will be online as a result of this call.
	 */
	UFUNCTION(BlueprintCallable)
	void EnableSDK();

	/**
	 * Disables the Braze SDK. This call persists across Braze SDK instances until enableSdk(Context) is called.
	 * Any in-flight actions such as event logging, data syncing, etc. will be dropped and not retried as a result of this call.
	 * Any stored instances of BrazeInstance should not be used. 
	 * All network requests for subsequent invocations of the Braze SDK (including new instances) will be offline. To re-enable 
	 * network requests and Braze SDK functionality, call EnableSDK
	 */
	UFUNCTION(BlueprintCallable)
	void DisableSDK();

	/**
	 * Hard resets all data created by the Braze SDK from the internal storage directory. Note that any in-flight actions 
	 * such as event logging, data syncing, etc. will be cancelled as a result of this call.
	 * Note that any references to BrazeInstance will be unusable after this call. 
	 */
	UFUNCTION(BlueprintCallable)
	void WipeData();

protected:

	UPROPERTY(BlueprintReadOnly)
	UBraze* BrazeInstance;

};
