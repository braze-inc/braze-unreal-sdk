// Copyright Braze Inc. All Rights Reserved.

#include "BrazeIOS.h"
#include "BrazeModule.h"

#if PLATFORM_IOS

#include "BrazeConfig.h"
#include "BrazeConversions.h"
#include "BrazeUserIOS.h"
#include "IOS/IOSAppDelegate.h"
#import "IOS/BrazeNotificationDelegate.h"
#import "IOS/AppboySDK/Appboy.h"
#import "BrazeNotificationSwizzling.h"
#import "BrazeUniversalLinkForwarder.h"

bool UBrazeIOS::Init(const UBrazeConfig& Config)
{
	if (Config.IOSApiKey.IsEmpty())
	{
		UE_LOG(LogBraze, Warning, TEXT("%s - Can not initialize: Empty API Key"), *GetName());
		return false;
	}

	dispatch_sync(dispatch_get_main_queue(), ^{
		[BrazeNotificationSwizzling swizzle];

		UIApplication * Application = [UIApplication sharedApplication];
		IOSAppDelegate * AppDelegate = (IOSAppDelegate*)[Application delegate];

		NSMutableDictionary* AppboyOptions = [[NSMutableDictionary alloc] init];
		if (!Config.CustomEndpoint.IsEmpty())
		{
			AppboyOptions[ABKEndpointKey] = BrazeConversions::FStringToNSString(Config.CustomEndpoint);
		}

		AppboyOptions[ABKEnableAutomaticLocationCollectionKey] = [NSNumber numberWithBool: Config.bIsLocationCollectionEnabled];
		AppboyOptions[ABKEnableGeofencesKey] = [NSNumber numberWithBool: Config.bGeofencesEnabled];
		AppboyOptions[ABKDisableAutomaticGeofenceRequestsKey] = [NSNumber numberWithBool: !Config.bAutomaticGeofenceRequestsEnabled];
		AppboyOptions[ABKSessionTimeoutKey] = [NSNumber numberWithInt: Config.SessionTimeout];
		AppboyOptions[ABKMinimumTriggerTimeIntervalKey] = [NSNumber numberWithInt: Config.TriggerActionMinimumTimeIntervalSeconds];
		AppboyOptions[ABKRequestProcessingPolicyOptionKey] = [NSNumber numberWithInt: Config.bIsAutomaticFlushEnabled ? ABKRequestProcessingPolicy::ABKAutomaticRequestProcessing : ABKRequestProcessingPolicy::ABKManualRequestProcessing];
		AppboyOptions[ABKFlushIntervalOptionKey] = [NSNumber numberWithFloat: Config.FlushInterval];

		[Appboy startWithApiKey: BrazeConversions::FStringToNSString(Config.IOSApiKey)
		          inApplication: Application
		      withLaunchOptions: AppDelegate.launchOptions
		      withAppboyOptions: AppboyOptions];

    [[Appboy sharedInstance] addSdkMetadata:@[ABKSdkMetadataUnreal]];
    [Appboy sharedInstance].appboyUrlDelegate = [BrazeUniversalLinkForwarder sharedInstance];
	});

	// Enable Push Notifications
	// - The notification device token is retrieved via method swizzling
	// - See: `[BrazeNotificationSwizzling swizzle]` implementation

	dispatch_sync(dispatch_get_main_queue(), ^ {
		UNAuthorizationOptions options = UNAuthorizationOptionAlert | UNAuthorizationOptionSound | UNAuthorizationOptionBadge;
			
		if (@available(iOS 12.0,*)) {
			options = options | UNAuthorizationOptionProvisional;
		}
			
		UNUserNotificationCenter* Center = [UNUserNotificationCenter currentNotificationCenter];
		
		if (Config.bEnableIOSPushDelegate)
		{
			BrazeNotificationDelegate* NotificationDelegate = [BrazeNotificationDelegate SharedInstance];
			Center.delegate = NotificationDelegate;
			NotificationDelegate.ShowPushNotificationsWhenAppInForeground = Config.bShowPushWhenAppInForeground;
		}
		
		[Center requestAuthorizationWithOptions: options
		                      completionHandler: ^(BOOL granted, NSError * _Nullable error)
		{
			[[Appboy sharedInstance] pushAuthorizationFromUserNotificationCenter: granted];
		}];
		
		[[UIApplication sharedApplication] registerForRemoteNotifications];
	});
	
	return true;
}

void UBrazeIOS::ChangeUser(const FString& UserId)
{
	dispatch_sync(dispatch_get_main_queue(), ^ {
		[[Appboy sharedInstance] changeUser: BrazeConversions::FStringToNSString(UserId)];
	});
}

void UBrazeIOS::LogCustomEvent(const FString& EventName)
{
	dispatch_sync(dispatch_get_main_queue(), ^ {
		[[Appboy sharedInstance] logCustomEvent: BrazeConversions::FStringToNSString(EventName)];
	});
}

void UBrazeIOS::LogCustomEventWithProperties(const FString& EventName, const FBrazeProperties& Properties)
{
	dispatch_sync(dispatch_get_main_queue(), ^ {
		[[Appboy sharedInstance] logCustomEvent: BrazeConversions::FStringToNSString(EventName) withProperties: BrazeConversions::FBrazePropertiesToNSDictionary(Properties)];
	});
}

void UBrazeIOS::LogPurchase(const FString& ProductIdentifier, const FString& CurrencyCode, const FString& Price, const uint8 Quantity)
{
	dispatch_sync(dispatch_get_main_queue(), ^ {
		[[Appboy sharedInstance] logPurchase: BrazeConversions::FStringToNSString(ProductIdentifier) inCurrency: BrazeConversions::FStringToNSString(CurrencyCode) atPrice: BrazeConversions::FStringToNSDecimalNumber(Price) withQuantity: Quantity];
	});
}

void UBrazeIOS::LogPurchaseWithProperties(const FString& ProductIdentifier, const FString& CurrencyCode, const FString& Price, const uint8 Quantity, const FBrazeProperties& Properties)
{
	dispatch_sync(dispatch_get_main_queue(), ^ {
		[[Appboy sharedInstance] logPurchase: BrazeConversions::FStringToNSString(ProductIdentifier) inCurrency: BrazeConversions::FStringToNSString(CurrencyCode) atPrice: BrazeConversions::FStringToNSDecimalNumber(Price) withQuantity: Quantity andProperties: BrazeConversions::FBrazePropertiesToNSDictionary(Properties)];
	});
}

void UBrazeIOS::RequestImmediateDataFlush()
{
	dispatch_sync(dispatch_get_main_queue(), ^{
		[[Appboy sharedInstance] flushDataAndProcessRequestQueue];
	});
}

UBrazeUser* UBrazeIOS::GetCurrentUser() const
{
	return NewObject<UBrazeUserIOS>();
}

#endif 
