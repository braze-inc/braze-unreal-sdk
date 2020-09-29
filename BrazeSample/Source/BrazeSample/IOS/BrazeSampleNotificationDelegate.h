// Copyright Braze Inc. All Rights Reserved.

#pragma once

#if PLATFORM_IOS

#import <UserNotifications/UserNotifications.h>

@interface BrazeSampleNotificationDelegate : NSObject<UNUserNotificationCenterDelegate>
+ (instancetype) SharedInstance;
@end

#endif
