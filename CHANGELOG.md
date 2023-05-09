## 2.5.0

##### Added
- Adds support for automatic universal links forwarding on iOS.
  - This enables the Braze SDK to automatically forward universal links to the iOS system method [`UIApplicationDelegate.application(_:continue:restorationHandler:)`](https://developer.apple.com/documentation/uikit/uiapplicationdelegate/1623072-application).
  - To enable this feature, you must add your app `<app name>.entitlements` file to the 'Copy Bundle Resources' build phase in Xcode.
    - In an Unreal Engine 4 project, the `<app name>.entitlements` file must be added to either `[YourProject]/Build/IOS` or `[YourProject]/Build/IOS/Cloud` depending on your setup.

## 2.4.0

##### Fixed
- Fixes iOS issues:
  - Use a method swizzling approach to handling notification device tokens to improve the Braze SDK compatibility with third party libraries.

## 2.3.0

##### Fixed
- Fixes text encoding issues on iOS. The plugin now correctly converts strings to UTF-8 before sending them to the Braze SDK.

## 2.2.0

##### Fixed
- Fixes Android issues:
  - Fixed issues with some `BrazeUser` functions causing crashes.

##### Updated
- Updates iOS support:
  - Framework rebuilt with Xcode 13 to support Xcode 13 build environment and platforms as old as iOS 9.

## 2.1.0

##### Updated
- Updates Android support:
  - Updates Braze Android SDK to version `24.1.0`.
  - Updates Gradle script generator to always include Kotlin plugin dependency, not just when `Firebase Cloud Messaging` is enabled.

##### Fixed
- Fixed an issue where a call to `Activity.registerActivityLifecycleCallbacks()` would cause a crash on API 28 and below devices.
## 2.0.0

##### Breaking
- Updates iOS support:
  - Updates the Braze iOS SDK to version `4.5.1`.
  - Switches the Braze static library to use the static framework.
- Updates Android support:
  - Updates Braze Android SDK to version `23.0`.
  - Updates supported Android SDK to `31`.
- Updates supported Unreal Engine version to `4.27`.

##### Added
- Adds the call to `addSdkMetadata` on both platforms to inform Braze services that this is an Unreal application.

## 1.0.0
- Initial release
