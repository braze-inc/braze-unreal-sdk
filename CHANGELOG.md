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