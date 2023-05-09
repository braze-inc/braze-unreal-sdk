// Copyright Braze Inc. All Rights Reserved.

#import <Foundation/Foundation.h>
#import "IOS/AppboySDK/ABKURLDelegate.h"

NS_ASSUME_NONNULL_BEGIN

@interface BrazeUniversalLinkForwarder : NSObject <ABKURLDelegate>

+ (instancetype)sharedInstance;

@end

NS_ASSUME_NONNULL_END
