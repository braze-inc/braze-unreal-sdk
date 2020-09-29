// Copyright Braze Inc. All Rights Reserved.

#include "BrazeSampleFunctionLibrary.h"
#include "BrazeConfig.h"

#if PLATFORM_IOS

#import "IOS/BrazeSampleNotificationDelegate.h"
#import <UserNotifications/UserNotifications.h>

#endif

void UBrazeSampleFunctionLibrary::ConnectIOSNotificationDelegate()
{
	const UBrazeConfig* const Config = UBrazeConfig::StaticClass()->GetDefaultObject<UBrazeConfig>();
	if (Config->bEnableIOSPushDelegate)
	{
		return;
	}
	
#if PLATFORM_IOS
	BrazeSampleNotificationDelegate* const NotificationDelegate = [BrazeSampleNotificationDelegate SharedInstance];
	UNUserNotificationCenter* const Center = [UNUserNotificationCenter currentNotificationCenter];
	Center.delegate = NotificationDelegate;
	
#endif
}
