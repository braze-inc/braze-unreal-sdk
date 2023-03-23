// Copyright Braze Inc. All Rights Reserved.

#import "BrazeNotificationSwizzling.h"

#import <UIKit/UIKit.h>
#import <objc/runtime.h>
#import "IOS/AppboySDK/Appboy.h"

// MARK: - Selector Definitions

@interface UIApplication (BRZSwizzling)

- (void)brz_application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;

@end

// MARK: - Braze Implementations

void brz_applicationDidRegisterForRemoteNotificationsWithDeviceTokenImplementation(id self, SEL _cmd, id application, id deviceToken) {
    // Braze handling
    [[Appboy sharedInstance] registerDeviceToken:deviceToken];
    
    // Execute default implementation
    if ([self respondsToSelector:@selector(brz_application:didRegisterForRemoteNotificationsWithDeviceToken:)]) {
        [self brz_application:application didRegisterForRemoteNotificationsWithDeviceToken:deviceToken];
    }
}

// MARK: - Swizzling

@implementation BrazeNotificationSwizzling

+ (void)swizzle {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        [BrazeNotificationSwizzling swizzleDidRegisterForRemoteNotificationsWithDeviceToken];
    });
}

+ (void)swizzleDidRegisterForRemoteNotificationsWithDeviceToken {
    // Get current ApplicationDelegate instance
    id<UIApplicationDelegate> delegate = UIApplication.sharedApplication.delegate;
    Class AppDelegate = [delegate class];
    
    SEL originalSel = @selector(application:didRegisterForRemoteNotificationsWithDeviceToken:);
    SEL swizzledSel = @selector(brz_application:didRegisterForRemoteNotificationsWithDeviceToken:);
    IMP swizzledImp = (IMP)brz_applicationDidRegisterForRemoteNotificationsWithDeviceTokenImplementation;
    const char * types = "v@:::";
    
    Method method = class_getInstanceMethod(AppDelegate, originalSel);
    
    if (method != nil) {
        class_addMethod(AppDelegate, swizzledSel, swizzledImp, types);
        method_exchangeImplementations(method, class_getInstanceMethod(AppDelegate, swizzledSel));
    } else {
        class_addMethod(AppDelegate, originalSel, swizzledImp, types);
    }
}

@end
