// Copyright Braze Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BrazeConfig.generated.h"

UCLASS(BlueprintType, config=Engine)
class BRAZE_API UBrazeConfig : public UObject
{
	GENERATED_BODY()
	
public:

	/** AutoInitialize Braze on start-up of the Engine using the Keys and Endpoint from this config  */
	UPROPERTY(config, EditAnywhere);
	bool bAutoInitialize = true;

	/** API Key to use on the Android platform */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category="Android")
	FString AndroidApiKey;

	/** API Key to use on the iOS Platform */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category="IOS")
	FString IOSApiKey;

	/** A CustomEndpoint to use, if applicable */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere)
	FString CustomEndpoint;

	/**
	 * This boolean sets whether Braze should automatically collect location (if the user permits). 
	 * If set to true, location data will be collected once at the start of each session. 
	 * If set to false, all location collection will be disabled and location will never be set for the user unless SetLastKnowLocation is manually called.
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere)
	bool bIsLocationCollectionEnabled = false;
	
	/**
	 * Gets whether the Braze Geofences feature is enabled.
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere)
	bool bGeofencesEnabled = false;
	
	/** Sets whether Braze Geofences are automatically requested by the Braze SDK. */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere)
	bool bAutomaticGeofenceRequestsEnabled = true;

	/**
	 * The length of time before a session times out in seconds. 
	 * The session manager will "re-open" otherwise closed sessions if the call to StartSession comes within this interval.
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere)
	int32 SessionTimeout = 10;
	
	/**
	 * The minimum interval in seconds between actions, such as an in-app message, that can be triggered by an in-app event, such as the logging of a custom event. 
	 * This is a general rate limit for actions to prevent overloading a user with messages.
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere)
	int32 TriggerActionMinimumTimeIntervalSeconds = 30;

	/**
	 *  IOS Only
	 *  If true, All server communication is handled automatically. This includes flushing
	 *  analytics data to the server, updating the feed, and requesting new in-app messages. Braze's
	 *  communication policy is to perform immediate server requests when user facing data is required (new in-app messages,
	 *  feed refreshes, etc.), and to otherwise perform periodic flushes of new analytics data every few seconds.
	 *  The interval between periodic flushes can be set explicitly using the FlushInterval config option
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category="IOS")
	bool bIsAutomaticFlushEnabled = true;

	/**
	 * IOS Only
	 * Sets the data flush interval (in seconds). This only has an effect when Automatic flush is enabled.
	 * Values must be greater than 1.0.
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "IOS")
	float FlushInterval = 10.0f;

	/**
	 * IOS Only
	 * Enable the Push Delegate. The Push Delegate overrides Unreal's UserNoticationCenter handlers and calls the Braze
	 * Analytics functions instead.
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "IOS")
	bool bEnableIOSPushDelegate = true;
	
	/**
	 * IOS Only
	 * Allows Push notifications to show while the app is in the foreground (otherwise they'll be silent)
	 * Note: Ignored if bEnableIOSPushDelegate = false
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "IOS")
	bool bShowPushWhenAppInForeground = true;
	
	/** 
	 * Android Only
	 * Sets the NotificationChannel user facing name for the Braze default NotificationChannel. 
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Android")
	FString DefaultNotificationChannelName = "";
	
	/**
	 * Android Only
	 * Sets the NotificationChannel user facing description for the Braze default NotificationChannel. 
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Android")
	FString DefaultNotificationChannelDescription = "";
	
	/**
	 * Android Only
	 * This integer sets the default accent color for push notifications on Android Lollipop and higher. 
	 * If not specified, the default background color is gray (the same gray Lollipop uses for system notifications).
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Android")
	int32 DefaultNotificationAccentColor = 0xFFF33E3E;
	
	/**
	 * Android Only
	 * Sets the data flush interval on GPRS and EDGE.
	 * To disable automatic flushing in this network condition, simply set the value to -1.
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Android")
	int32 BadNetworkDataFlushInterval = 60;
	
	/**
	 * Android Only
	 * Sets the data flush interval on GPRS and EDGE.
	 * To disable automatic flushing in this network condition, simply set the value to -1.
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Android")
	int32 GoodNetworkDataFlushInterval = 30;
	
	/**
	 * Android Only
	 * Sets the data flush interval on 4G or Wifi.
	 * To disable automatic flushing in this network condition, simply set the value to -1.
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Android")
	int32 GreatNetworkDataFlushInterval = 10;
	
	/**
	 * Android Only
	 * Sets the session timeout behavior to be either session-start or session-end based. 
	 * When true, the session timeout and eventual session end is calculated using the timestamp of the start of the session. 
	 * When false, the session timeout and eventual session end is calculated using the end of the session.
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Android")
	bool bIsSessionStartBasedTimeoutEnabled = false;
	
	/**
	 * Android Only
	 * In order to use FirebaseCloudMessaging, this must be enabled at build time (and not run-time) due to changes to the build process required by enabling Firebase Cloud Messaging.
	 * Add bEnabledFirebaseCloudMessagingSupport=true to your engine.ini file under the [/Script/Braze.BrazeConfig] section for FCM support
	 */
	UPROPERTY(config, EditAnywhere, Category = "Android")
	bool bEnableFirebaseCloudMessagingSupport = false;

	/** 
	 * Android Only
	 * Sets whether the SDK to automatically register for Firebase Cloud Messaging. When manually passing push tokens to Braze, this setting should be disabled. 
	 * NOTE: Ignored if bEnableFirebaseCloudMessagingSupport is false
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Android")
	bool bIsFirebaseCloudMessagingRegistrationEnabled = false;
	
	/**
	 * Android Only
	 * Sets the sender ID key used to register for Firebase Cloud Messaging.
	 * NOTE: Ignored if bEnableFirebaseCloudMessagingSupport is false or if bIsFirebaseCloudMessageRegistrationEnabled is false
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Android")
	FString FirebaseCloudMessagingSenderIdKey;

	/**
	  * Android Only
	  * Sets whether a screen wakelock will be acquired to wake the device screen for push notifications. 
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Android")
	bool bIsPushWakeScreenForNotificationEnabled = true;
	
	/**
	 * Android Only
	 * Sets whether a the text content in push notifications should be interpreted and rendered as Html using Html.fromHtml(String, int).
	 */
	UPROPERTY(BlueprintReadWrite, config, EditAnywhere, Category = "Android")
	bool bPushHtmlRenderingEnabled = false;
	
	/**
	 * Android Only
	 * When true, sets the Newsfeed visual indicator for read/unread status to be enabled.
	 * NOT Supported in Braze Unreal SDK 
	 */
	UPROPERTY(config)
	bool bNewsFeedVisualIndicatorOn = true;

	/**
	 * Android Only
	 * Enables automatic registration for Amazon Device Messaging. When manually passing ADM push tokens to Braze, this setting should be disabled. 
	 * NOT Supported in Braze Unreal SDK 
	 */
	UPROPERTY(config)
	bool bAdmMessagingRegistrationEnabled = false;
	
	/** 
	 * Android Only
	 * Sets whether the Content Cards unread visual indication bar is enabled. 
	 * NOT Supported in Braze Unreal SDK
	 */
	UPROPERTY(config)
	bool bContentCardsUnreadVisualIndicatorEnabled = false;
	
	/**
	 * Android Only
	 * In-app message accessibility exclusive mode, when enabled, forces accessibility readers to only be able to read currently displaying in-app messages and no other screen contents. 
	 * A common use for this feature is the desire to prevent Android TalkBack from reading out UI elements "behind" a currently displaying in-app message.
	 * NOT Supported in Braze Unreal SDK
	 */
	UPROPERTY(config)
	bool bIsInAppMessageAccessibilityExclusiveModeEnabled = false;
	
	/**
	 * Android Only
	 * Gets whether the In-App Message Test Push will attempt to automatically display the test In-App Message without the need for clicking on a push beforehand. 
	 * If the app is in the background or otherwise can't immediately display the In-App Message, a push will be displayed instead.
	 * NOT Supported in Braze Unreal SDK
	 */
	UPROPERTY(config)
	bool bInAppMessageTestPushEagerDisplayEnabled = false;
	
};
