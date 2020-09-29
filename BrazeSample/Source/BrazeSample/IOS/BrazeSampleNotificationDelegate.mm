// Copyright Braze Inc. All Rights Reserved.

#if PLATFORM_IOS

#import "BrazeSampleNotificationDelegate.h"
#import "IOS/BrazeNotificationDelegate.h"

@implementation BrazeSampleNotificationDelegate

+ (instancetype) SharedInstance
{
	static BrazeSampleNotificationDelegate* Instance = nil;
	static dispatch_once_t pred;
	dispatch_once(&pred, ^{
		Instance = [BrazeSampleNotificationDelegate new];
	});
	
	return Instance;
}

- (void)userNotificationCenter:(UNUserNotificationCenter*) Center
didReceiveNotificationResponse:(UNNotificationResponse*) Response
		 withCompletionHandler:(void (^)(void)) CompletionHandler
{
	/*
	 
	 Your own code / other plugin handling of push notifications here...
	 
	 */
	
	
	[[BrazeNotificationDelegate SharedInstance] userNotificationCenter: Center
	                                    didReceiveNotificationResponse: Response
	                                             withCompletionHandler: CompletionHandler];
}

- (void)userNotificationCenter:(UNUserNotificationCenter*) Center
       willPresentNotification:(UNNotification*) Notification
         withCompletionHandler:(void(^)(UNNotificationPresentationOptions Options)) CompletionHandler
{
	CompletionHandler(UNNotificationPresentationOptionAlert);
}

@end

#endif
