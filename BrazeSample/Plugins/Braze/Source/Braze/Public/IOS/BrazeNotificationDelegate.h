// Copyright Braze Inc. All Rights Reserved.

#pragma once

#if PLATFORM_IOS

#import <UserNotifications/UserNotifications.h>

@interface BrazeNotificationDelegate : NSObject<UNUserNotificationCenterDelegate>

+ (instancetype) SharedInstance;

@property bool ShowPushNotificationsWhenAppInForeground;

@end

#endif
