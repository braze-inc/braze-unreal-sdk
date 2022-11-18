# Braze Unreal SDK

The Braze Unreal SDK integrates the Braze SDK for Android and iOS with UE4. Android and iOS are the only supported platforms.

## Setup
### Content

The Braze Unreal SDK has two parts:
1. Braze Plugin - Located in BrazeSample/Plugins/Braze. This is the module that provides Braze functionality, which you will integrate into your own app.
2. Braze Sample - This is a sample project demonstrating the integration of the Braze Plugin. Use this as a helpful reference for using the plugin.

### Integrating the Plugin

1. Copy BrazeSample/Plugins/Braze into your own app's Plugin folder.
2. Enable the Plugin  
   * If using a C++ Project, configure your module to reference the Braze module. In your \*.Build.cs file, add "Braze" to your PublicDependencyModuleNames. Ex:
   ```
   PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Braze" });
   ```
   * In a Blueprint Project, enable the plugin by first clicking Settings->Plugins, scrolling down to Projects section of plugins, and clicking Braze. From there you can tick the `Enabled` checkbox:
   ![EnablePlugin](../READMEImages/img/EnablePlugin.png)
3. Configure your DefaultEngine.ini with your API keys and your Endpoint. 
```
[/Script/Braze.BrazeConfig]
bAutoInitialize=True ; true by default, initialize when the project starts
AndroidApiKey= ; your API key
IOSApiKey= ; your API key
CustomEndpoint= ; your endpoint
```

> **Warning**
> For projects targeting Android SDK 31+ Unreal will generate builds that will fail during installation on Android 12+ devices with the INSTALL_PARSE_FAILED_MANIFEST_MALFORMED error. To fix this, locate the `UE4_Engine_AndroidSDK_31_Build_Fix.patch` git patch file in the root of this repository and apply it to your Unreal source build.

### Manually Initialize Braze

If you'd like precise control over when Braze initializes, you may disable AutoInitialize in the DefaultEngine.ini. With AutoInitialize disabled, you'll need to manually initialize Braze from native C++ or Blueprint.

In native C++, access the BrazeSubsystem and call `InitializeBraze()` optionally passing it a Config to override Engine.ini settings.

```
  UBrazeSubsystem* const BrazeSubsystem = GEngine->GetEngineSubsystem<UBrazeSubsystem>();
  UBraze* const BrazeInstance = BrazeSubsystem->InitializeBraze();
```

In Blueprint, the same functions are accessible as Blueprint nodes:  
Use the `GetBrazeSubsystem` Node to call its `Initialize` node.  
A BrazeConfig object can optionally be created in Blueprint and passed to `Initialize`

![InitializeBraze](../READMEImages/img/InitializeBraze.png)

### Logging

#### iOS
Enabling Braze SDK Level logging on iOS via the info.plist is also possible in UE4. Navigate Settings -> Project Settings, then navigate to IOS on the left pane (under the Platforms heading). In the Right pane, search for the `Extra PList Data` heading and in the `Additional Plist Data` field you can enter the following to specify logging verbosity from the SDK:

```
<key>Appboy</key>
<dict>
  <key>LogLevel</key>
  <string>0</string>
</dict>
```

The default log level is 8, which is minimal logging. Read more about log levels: [Other SDK Customization](https://www.braze.com/docs/developer_guide/platform_integration_guides/ios/initial_sdk_setup/other_sdk_customizations/)

#### Android
On Android, Enabling Braze SDK Level Logging is done at runtime by calling `UBrazeSubsystem::AndroidSetLogLevel`.

```
  UBrazeSubsystem* const BrazeSubsystem = GEngine->GetEngineSubsystem<UBrazeSubsystem>();
  BrazeSubsystem->AndroidSetLogLevel(EBrazeLogLevel::Verbose);
  UBraze* const BrazeInstance = BrazeSubsystem->InitializeBraze();
```

In Blueprint, the same function is accessible as a node:

![AndroidSetLogLevel](../READMEImages/img/AndroidSetLogLevel.png)

In order to ensure logging is set when the Braze SDK Initialize is called, it is recommended to call this before `InitializeBraze`.

## Features

### Analytics

The Braze Unreal SDK supports the following analytics functions. Read more about using Braze in the [Braze Documentation](https://www.braze.com/docs/).

UBraze functions:
* ChangeUser
* LogCustomEvent
* LogCustomEventWithProperties
* LogPurchase
* LogPurchaseWithProperties
* RequestImmediateDataFlush
* GetCurrentUser

UBrazeUser functions:
* SetCustomUserAttribute* - Supports String, Int, Long, Float, Bool, Date
* SetCustomAttributeArray
* UnsetCustomAttribute
* IncrementCustomUserAttribute
* AddToCustomAttributeArray
* RemoveFromCustomAttributeArray
* SetEmail
* SetFirstName
* SetLastName
* SetGender
* SetLanguage
* SetCountry
* SetHomeCity
* SetPhoneNumber
* SetDateOfBirth
* SetPushSubscriptionType
* SetEmailSubscriptionType
* SetAttributionData
* SetLastKnownLocation

#### Creating FBrazeProperties in Blueprint

The Blueprint Library BrazePropertiesLibrary includes helper functions to make creating BrazeProperties easier. Use the `Make FBrazeAny*` Nodes with a `MakeMap` when using the `MakeBrazeProperties` node. For example:

![MakeBrazeProperties](../READMEImages/img/MakeBrazeProperties.png)

### Push Notifications

#### Android

In order to enable Push Notifications to Android via Firebase Coud Messaging (FCM), do the following:
1. Add the following lines to your engine.ini for your project:
    * bEnableFirebaseCloudMessagingSupport=true
    * bIsFirebaseCloudMessagingRegistrationEnabled=true
2. Setup your application with [FCM](https://firebase.google.com/docs/cloud-messaging/)
3. Add FirebaseCloudMessagingSenderIdKey=<your sender id key> to your engine.ini for your project.
    * Also See Step 4 of the [Braze Integration](https://www.braze.com/docs/developer_guide/platform_integration_guides/android/push_notifications/android/integration/standard_integration) document to setup your credentials on the dashboard.
4. Create `AndroidCopies` folder next to the [BrazeUPLAndroid.xml](./BrazeSample/Plugins/Braze/Source/Braze/BrazeUPLAndroid.xml). Add your `google-services.json` to the top of this folder.

To set the [small and large notification icons](https://www.braze.com/docs/developer_guide/platform_integration_guides/android/push_notifications/android/integration/standard_integration#step-3-configure-notification-icons):
1. Add icons to the appropriate drawable folder (`drawable` by default) inside of the `AndroidCopies/res` folder.
2. Add `braze.xml` to the `AndroidCopies/res/values` folder to set the icons. A very basic braze.xml file:
```
<?xml version="1.0" encoding="utf-8"?>
<resources>
    <drawable name="com_braze_push_small_notification_icon">@drawable/notification_small_icon</drawable>
    <drawable name="com_braze_push_large_notification_icon">@drawable/notification_large_icon</drawable>
</resources>
```
> **Note**
> The files from the `AndroidCopies` folder will be copied into the generated Android project structure as defined in the `BrazeUPLAndroid.xml`.

#### iOS

In order to enable Push Notifications to iOS, do the following:  
1. Follow the first step from the [Braze Integration](https://www.braze.com/docs/developer_guide/platform_integration_guides/ios/push_notifications/integration/#step-1-configure-push-notifications) document to create your P8. 
2. "Enable Remote Notifications Support" under Settings -> Project Settings -> iOS -> Online to setup your project for Push Capabilities
    *   In order to do this, the project must be built using Engine Source. 
3. Make sure your provision has Push capabilities enabled.

##### Support for Remote Launch Notifications

As of 4.25.3, UE4 lacks proper support to receive a remote notification that causes the initial launch of the application. In order to support receiving this notification, we've created two git patches to apply - one for UE4 and one for the Braze SDK plugin.

1. To your UE4 Engine Source folder, apply the git patch `UE4_Engine-Cache-Launch-Remote-Notification.patch`
2. To the Braze Unreal SDK folder, apply the git patch `Braze_SDK-Read-Cached-Remote-Launch-Notification.patch`
