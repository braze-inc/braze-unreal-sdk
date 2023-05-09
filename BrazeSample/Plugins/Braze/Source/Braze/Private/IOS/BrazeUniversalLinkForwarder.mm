// #include "CoreMinimal.h"
#include "BrazeModule.h"
#import "BrazeUniversalLinkForwarder.h"
//#import "ABKLogger.h"

@interface BrazeUniversalLinkForwarder ()

@property (strong, nonatomic) NSSet<NSString *> *applinks;

@end

@implementation BrazeUniversalLinkForwarder

+ (instancetype)sharedInstance {
  static BrazeUniversalLinkForwarder *shared = nil;
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^{
    shared = [[self alloc] init];
  });
  return shared;
}

- (instancetype)init {
  self = [super init];
  if (self) {
    _applinks = [BrazeUniversalLinkForwarder applinksFromEntitlements];
  }
  return self;
}

- (BOOL)handleAppboyURL:(NSURL *)url
            fromChannel:(ABKChannel)channel
             withExtras:(NSDictionary *)extras {
  NSString *host = url.host;
  if (!host) {
    return NO;
  }

  // Forward universal links URLs to the app delegate
  if ([self.applinks containsObject:host]) {
    UE_LOG(LogBraze, Log, TEXT("Forwarding universal link to 'UIApplicationDelegate.application:continueUserActivity:restorationHandler:' (%s)."), UTF8_TO_TCHAR(url.absoluteString.UTF8String));
    UIApplication *app = UIApplication.sharedApplication;
    NSUserActivity* userActivity = [[NSUserActivity alloc] initWithActivityType:NSUserActivityTypeBrowsingWeb];
    userActivity.webpageURL = url;
    [app.delegate application:app
         continueUserActivity:userActivity restorationHandler:^(NSArray<id<UIUserActivityRestoring>> * _Nullable restorableObjects) {}];
    return YES;
  }

  return NO;
}

// MARK: - Private Methods

/// Reads the associated domains' applinks entries from the application `.entitlements` file.
+ (NSSet<NSString *> *)applinksFromEntitlements {
  // Get entitlements
  NSURL *entitlementsURL = [NSBundle.mainBundle URLsForResourcesWithExtension:@"entitlements"
                                                                 subdirectory:nil].firstObject;
  if (entitlementsURL == nil) {
    UE_LOG(LogBraze, Log, TEXT("No '.entitlements' file found in the application main bundle, automatic universal link forwarding is disabled. To enable automatic universal link forwarding, make sure that your '<app name>.entitlements' file is added to the 'Copy Bundle Resources' build phase in Xcode. (bundle path: %s). In the Unreal Engine, the file must be added to either `[YourProject]/Build/IOS` or `[YourProject]/Build/IOS/Cloud` depending on your setup. The file must be named `<app name>.entitlements`"), UTF8_TO_TCHAR(NSBundle.mainBundle.bundleURL.path.UTF8String));
    return [NSSet set];
  }
  NSDictionary *entitlements = [NSDictionary dictionaryWithContentsOfURL:entitlementsURL];

  // Retrieve associated domains
  NSArray<NSString *> *associatedDomains = entitlements[@"com.apple.developer.associated-domains"];
  if (associatedDomains == nil || associatedDomains.count == 0) {
    UE_LOG(LogBraze, Log, TEXT("No associated domains found in '.entitlements' file, automatic universal link forwarding is disabled."));
    return [NSSet set];
  }

  // Filter applinks
  NSMutableArray<NSString *> *appLinks = [NSMutableArray array];
  for (NSString *associatedDomain in associatedDomains) {
    if ([associatedDomain hasPrefix:@"applinks:"]) {
      NSString *domain = [associatedDomain stringByReplacingOccurrencesOfString:@"applinks:" withString:@""];
      [appLinks addObject:domain];
    }
  }

  if (appLinks.count == 0) {
    UE_LOG(LogBraze, Log, TEXT("No applinks associated domains found in '.entitlements' file, automatic universal link forwarding is disabled."));
    return [NSSet set];
  }

  NSString *appLinksDescription = [appLinks description];
  UE_LOG(LogBraze, Log, TEXT("Found applinks associated domains, automatic universal link forwarding is enabled for %s."), UTF8_TO_TCHAR(appLinksDescription.UTF8String));
  return [NSSet setWithArray:appLinks];
}

@end
