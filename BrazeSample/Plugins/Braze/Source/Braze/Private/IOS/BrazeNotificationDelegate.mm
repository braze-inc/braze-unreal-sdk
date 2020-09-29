// Copyright Braze Inc. All Rights Reserved.

#if PLATFORM_IOS

#include "Braze.h"
#include "Async/TaskGraphInterfaces.h"
#include "BrazeModule.h"
#include "IOS/IOSAppDelegate.h"
#include "Misc/CoreDelegates.h"

#import "IOS/BrazeNotificationDelegate.h"
#import "IOS/AppboySDK/Appboy.h"

@implementation BrazeNotificationDelegate

@synthesize ShowPushNotificationsWhenAppInForeground;

- (id)init
{
	if (self = [super init])
	{
		self.ShowPushNotificationsWhenAppInForeground = true;
	}
	
	return self;
}

+ (instancetype) SharedInstance
{
	static BrazeNotificationDelegate* Instance = nil;
	static dispatch_once_t pred;
	dispatch_once(&pred, ^{
		Instance = [BrazeNotificationDelegate new];
	});
	
	return Instance;
}

namespace 
{
	void HandleReceivedNotification(UNNotification* notification)
	{
		bool IsLocal = false;
	
		if ([IOSAppDelegate GetDelegate].bEngineInit)
		{
			NSString* NotificationType = (NSString*)[notification.request.content.userInfo objectForKey: @"NotificationType"];
			if(NotificationType != nullptr)
			{
				FString LocalOrRemote(NotificationType);
				if(LocalOrRemote == FString(TEXT("Local")))
				{
					IsLocal = true;
				}
			}
		
			int AppState;
			if ([UIApplication sharedApplication].applicationState == UIApplicationStateInactive)
			{
				AppState = 1; // EApplicationState::Inactive;
			}
			else if ([UIApplication sharedApplication].applicationState == UIApplicationStateBackground)
			{
				AppState = 2; // EApplicationState::Background;
			}
			else
			{
				AppState = 3; // EApplicationState::Active;
			}
		
			if(IsLocal)
			{
				NSString*	activationEvent = (NSString*)[notification.request.content.userInfo objectForKey: @"ActivationEvent"];
				if(activationEvent != nullptr)
				{
					FString	activationEventFString(activationEvent);
					int32	fireDate = [notification.date timeIntervalSince1970];
				
					FFunctionGraphTask::CreateAndDispatchWhenReady([activationEventFString, fireDate, AppState]()
																   {
																	   FCoreDelegates::ApplicationReceivedLocalNotificationDelegate.Broadcast(activationEventFString, fireDate, AppState);
																   }, TStatId(), NULL, ENamedThreads::GameThread);
				}
			}
			else
			{
				NSString* JsonString = @"{}";
				NSError* JsonError;
				NSData* JsonData = [NSJSONSerialization dataWithJSONObject : notification.request.content.userInfo
																   options : 0
																	 error : &JsonError];
			
				if (JsonData)
				{
					JsonString = [[[NSString alloc] initWithData:JsonData encoding : NSUTF8StringEncoding] autorelease];
				}
			
				FString	jsonFString(JsonString);
			
				FFunctionGraphTask::CreateAndDispatchWhenReady([jsonFString, AppState]()
															   {
																   FCoreDelegates::ApplicationReceivedRemoteNotificationDelegate.Broadcast(jsonFString, AppState);
															   }, TStatId(), NULL, ENamedThreads::GameThread);
			}
		}
	}
}

- (void)userNotificationCenter:(UNUserNotificationCenter*) Center
didReceiveNotificationResponse:(UNNotificationResponse*) Response
		 withCompletionHandler:(void (^)(void)) CompletionHandler
{
	HandleReceivedNotification(Response.notification);
	[[Appboy sharedInstance] userNotificationCenter: Center
	                 didReceiveNotificationResponse: Response
	                          withCompletionHandler: CompletionHandler];
	
}

- (void)userNotificationCenter:(UNUserNotificationCenter*) Center
       willPresentNotification:(UNNotification*) Notification
         withCompletionHandler:(void(^)(UNNotificationPresentationOptions Options)) CompletionHandler
{

	HandleReceivedNotification(Notification);

	if (self.ShowPushNotificationsWhenAppInForeground)
	{
		CompletionHandler(UNNotificationPresentationOptionAlert);
	}
	else
	{
		CompletionHandler(UNNotificationPresentationOptionNone);
	}
}

@end

#endif 
