// Copyright Braze Inc. All Rights Reserved.

#include "BrazeAndroid.h"
#include "BrazeConfig.h"
#include "BrazeModule.h"
#include "BrazeSubsystem.h"

#if PLATFORM_ANDROID
#include "BrazeConversions.h"
#include "Android/BrazeUserAndroid.h"

void UBrazeAndroid::BeginDestroy()
{
	Super::BeginDestroy();

	if (JNIEnv* const Env = FAndroidApplication::GetJavaEnv())
	{
		Env->DeleteLocalRef(ApplicationContext);
	}
}

bool UBrazeAndroid::Init(const UBrazeConfig& Config)
{
	if (Config.AndroidApiKey.IsEmpty())
	{
		UE_LOG(LogBraze, Warning, TEXT("%s - Can not initialize: Empty API Key"), *GetName());
		return false;
	}

	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();

	const jmethodID MethodGetApplicationContext = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "getApplicationContext", "()Landroid/content/Context;", false);
	ApplicationContext = FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, MethodGetApplicationContext);

	// Retrieve all the builder setters
	const jclass ClassAppboyConfigBuilder = FAndroidApplication::FindJavaClass("com/appboy/configuration/AppboyConfig$Builder");
	const jmethodID MethodSetApiKey = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setApiKey", "(Ljava/lang/String;)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetDefaultNotificationChannelName = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setDefaultNotificationChannelName", "(Ljava/lang/String;)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetDefaultNotificationChannelDescription = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setDefaultNotificationChannelDescription", "(Ljava/lang/String;)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetNewsfeedVisualIndicatorOn = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setNewsfeedVisualIndicatorOn", "(Z)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetCustomEndpoint = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setCustomEndpoint", "(Ljava/lang/String;)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetSessionTimeout = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setSessionTimeout", "(I)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetDefaultNotificationAccentColor = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setDefaultNotificationAccentColor", "(I)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetTriggerActionMinimumTimeIntervalSeconds = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setTriggerActionMinimumTimeIntervalSeconds", "(I)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetAdmMessagingRegistrationEnabled = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setAdmMessagingRegistrationEnabled", "(Z)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetIsLocationCollectionEnabled = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setIsLocationCollectionEnabled", "(Z)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetBadNetworkDataFlushInterval = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setBadNetworkDataFlushInterval", "(I)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetGoodNetworkDataFlushInterval = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setGoodNetworkDataFlushInterval", "(I)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetGreatNetworkDataFlushInterval = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setGreatNetworkDataFlushInterval", "(I)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetIsSessionStartBasedTimeoutEnabled = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setIsSessionStartBasedTimeoutEnabled", "(Z)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetIsFirebaseCloudMessagingRegistrationEnabled = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setIsFirebaseCloudMessagingRegistrationEnabled", "(Z)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetFirebaseCloudMessagingSenderIdKey = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setFirebaseCloudMessagingSenderIdKey", "(Ljava/lang/String;)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetContentCardsUnreadVisualIndicatorEnabled = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setContentCardsUnreadVisualIndicatorEnabled", "(Z)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetIsInAppMessageAccessibilityExclusiveModeEnabled = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setIsInAppMessageAccessibilityExclusiveModeEnabled", "(Z)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetIsPushWakeScreenForNotificationEnabled = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setIsPushWakeScreenForNotificationEnabled", "(Z)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetPushHtmlRenderingEnabled = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setPushHtmlRenderingEnabled", "(Z)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetGeofencesEnabled = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setGeofencesEnabled", "(Z)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetInAppMessageTestPushEagerDisplayEnabled = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setInAppMessageTestPushEagerDisplayEnabled", "(Z)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetAutomaticGeofenceRequestsEnabled = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setAutomaticGeofenceRequestsEnabled", "(Z)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodSetHandlePushDeepLinksAutomatically = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "setHandlePushDeepLinksAutomatically", "(Z)Lcom/appboy/configuration/AppboyConfig$Builder;", false);
	const jmethodID MethodBuild = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "build", "()Lcom/appboy/configuration/AppboyConfig;", false);
	
	// begin building from config
	const jmethodID MethodInitBuilder = FJavaWrapper::FindMethod(Env, ClassAppboyConfigBuilder, "<init>", "()V", false);
	const FScopedJavaObject<jobject> Builder = NewScopedJavaObject(Env, Env->NewObject(ClassAppboyConfigBuilder, MethodInitBuilder));
	
	const FScopedJavaObject<jstring> ApiKey = FJavaHelper::ToJavaString(Env, Config.AndroidApiKey);
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetApiKey, *ApiKey));
	
	if (!Config.CustomEndpoint.IsEmpty())
	{
		const FScopedJavaObject<jstring> CustomEndpoint = FJavaHelper::ToJavaString(Env, Config.CustomEndpoint);
		Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetCustomEndpoint, *CustomEndpoint));
	}

	if (!Config.DefaultNotificationChannelName.IsEmpty())
	{
		const FScopedJavaObject<jstring> DefaultNotificationChannelName = FJavaHelper::ToJavaString(Env, Config.DefaultNotificationChannelName);
		Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetDefaultNotificationChannelName, *DefaultNotificationChannelName));
	}

	if (!Config.DefaultNotificationChannelDescription.IsEmpty())
	{
		const FScopedJavaObject<jstring> DefaultNotificationChannelDescription = FJavaHelper::ToJavaString(Env, Config.DefaultNotificationChannelDescription);
		Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetDefaultNotificationChannelDescription, *DefaultNotificationChannelDescription));
	}

	if (Config.bEnableFirebaseCloudMessagingSupport && Config.bIsFirebaseCloudMessagingRegistrationEnabled && !Config.FirebaseCloudMessagingSenderIdKey.IsEmpty())
	{
		const FScopedJavaObject<jstring> FirebaseCloudMessagingSenderIdKey = FJavaHelper::ToJavaString(Env, Config.FirebaseCloudMessagingSenderIdKey);

		Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetIsFirebaseCloudMessagingRegistrationEnabled, Config.bIsFirebaseCloudMessagingRegistrationEnabled));
		Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetFirebaseCloudMessagingSenderIdKey, *FirebaseCloudMessagingSenderIdKey));
		Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetHandlePushDeepLinksAutomatically, true));
	}
	else
	{
		Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetIsFirebaseCloudMessagingRegistrationEnabled, false));
	}

	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetNewsfeedVisualIndicatorOn, Config.bNewsFeedVisualIndicatorOn));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetSessionTimeout, Config.SessionTimeout));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetDefaultNotificationAccentColor, Config.DefaultNotificationAccentColor));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetTriggerActionMinimumTimeIntervalSeconds, Config.TriggerActionMinimumTimeIntervalSeconds));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetAdmMessagingRegistrationEnabled, Config.bAdmMessagingRegistrationEnabled));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetIsLocationCollectionEnabled, Config.bIsLocationCollectionEnabled));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetBadNetworkDataFlushInterval, Config.BadNetworkDataFlushInterval));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetGoodNetworkDataFlushInterval, Config.GoodNetworkDataFlushInterval));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetGreatNetworkDataFlushInterval, Config.GreatNetworkDataFlushInterval));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetIsSessionStartBasedTimeoutEnabled, Config.bIsSessionStartBasedTimeoutEnabled));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetContentCardsUnreadVisualIndicatorEnabled, Config.bContentCardsUnreadVisualIndicatorEnabled));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetIsInAppMessageAccessibilityExclusiveModeEnabled, Config.bIsInAppMessageAccessibilityExclusiveModeEnabled));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetIsPushWakeScreenForNotificationEnabled, Config.bIsPushWakeScreenForNotificationEnabled));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetPushHtmlRenderingEnabled, Config.bPushHtmlRenderingEnabled));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetGeofencesEnabled, Config.bGeofencesEnabled));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetInAppMessageTestPushEagerDisplayEnabled, Config.bInAppMessageTestPushEagerDisplayEnabled));
	Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetAutomaticGeofenceRequestsEnabled, Config.bAutomaticGeofenceRequestsEnabled));
	
	// build the AppboyConfig object
	const FScopedJavaObject<jobject> AppboyConfig = NewScopedJavaObject(Env, FJavaWrapper::CallObjectMethod(Env, *Builder, MethodBuild));
	
	const jclass ClassAppboy = FAndroidApplication::FindJavaClass("com/appboy/Appboy");
	const jmethodID MethodConfigure = FJavaWrapper::FindStaticMethod(Env, ClassAppboy, "configure", "(Landroid/content/Context;Lcom/appboy/configuration/AppboyConfig;)Z", false);
	Env->CallStaticBooleanMethod(ClassAppboy, MethodConfigure, ApplicationContext, *AppboyConfig);

	// register lifecycle callbacks listener
	const jclass ClassAppboyLifecycleCallbackListener = FAndroidApplication::FindJavaClass("com/appboy.AppboyLifecycleCallbackListener");
	const jmethodID MethodInitAppboyLifecycleCallbackListener = FJavaWrapper::FindMethod(Env, ClassAppboyLifecycleCallbackListener, "<init>", "()V", false);
	const FScopedJavaObject<jobject> AppboyLifecycleCallbackListener = NewScopedJavaObject(Env, Env->NewObject(ClassAppboyLifecycleCallbackListener, MethodInitAppboyLifecycleCallbackListener));
	const jmethodID MethodRegisterActivityLifecycleCallbacks = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "registerActivityLifecycleCallbacks", "(Landroid/app/Application$ActivityLifecycleCallbacks;)V", false);
	FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, MethodRegisterActivityLifecycleCallbacks, *AppboyLifecycleCallbackListener);

	return true;
}

FScopedJavaObject<jobject> UBrazeAndroid::GetAppboyInstance() const
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const jclass ClassAppboy = FAndroidApplication::FindJavaClass("com/appboy/Appboy");

	const jmethodID MethodGetInstance = Env->GetStaticMethodID(ClassAppboy, "getInstance", "(Landroid/content/Context;)Lcom/appboy/Appboy;");
	return FScopedJavaObject<jobject>(Env, Env->CallStaticObjectMethod(ClassAppboy, MethodGetInstance, ApplicationContext));
}

void UBrazeAndroid::ChangeUser(const FString& UserId)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jobject> AppboyInstance = GetAppboyInstance();
	const jclass ClassAppboy = FAndroidApplication::FindJavaClass("com/appboy/Appboy");

	const FScopedJavaObject<jstring> UserIdString = FJavaHelper::ToJavaString(Env, UserId);
	const jmethodID MethodChangeUser = FJavaWrapper::FindMethod(Env, ClassAppboy, "changeUser", "(Ljava/lang/String;)V", false);
	FJavaWrapper::CallVoidMethod(Env, *AppboyInstance, MethodChangeUser, *UserIdString);
}

void UBrazeAndroid::LogCustomEvent(const FString& EventName)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jobject> AppboyInstance = GetAppboyInstance();
	const jclass ClassAppboy = FAndroidApplication::FindJavaClass("com/appboy/Appboy");

	const FScopedJavaObject<jstring> EventString = FJavaHelper::ToJavaString(Env, EventName);
	const jmethodID MethodLogCustomEvent = FJavaWrapper::FindMethod(Env, ClassAppboy, "logCustomEvent", "(Ljava/lang/String;)V", false);
	FJavaWrapper::CallVoidMethod(Env, *AppboyInstance, MethodLogCustomEvent, *EventString);
}

void UBrazeAndroid::LogCustomEventWithProperties(const FString& EventName, const FBrazeProperties& Properties)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();

	const FScopedJavaObject<jobject> AppboyInstance = GetAppboyInstance();
	const jclass ClassAppboy = FAndroidApplication::FindJavaClass("com/appboy/Appboy");
	
	const FScopedJavaObject<jstring> EventString = FJavaHelper::ToJavaString(Env, EventName);
	const FScopedJavaObject<jobject> AppboyPropertiesInstance = BrazeConversions::ToJavaAppboyProperties(Properties);
	
	const jmethodID MethodLogCustomEvent = FJavaWrapper::FindMethod(Env, ClassAppboy, "logCustomEvent", "(Ljava/lang/String;Lcom/appboy/models/outgoing/AppboyProperties;)V", false);
	FJavaWrapper::CallVoidMethod(Env, *AppboyInstance, MethodLogCustomEvent, *EventString, *AppboyPropertiesInstance);
}

void UBrazeAndroid::LogPurchase(const FString& ProductIdentifier, const FString& CurrencyCode, const FString& Price, const uint8 Quantity)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jobject> AppboyInstance = GetAppboyInstance();
	const jclass ClassAppboy = FAndroidApplication::FindJavaClass("com/appboy/Appboy");

	const FScopedJavaObject<jstring> ProductIdentifierString = FJavaHelper::ToJavaString(Env, ProductIdentifier);
	const FScopedJavaObject<jstring> CurrencyCodeString = FJavaHelper::ToJavaString(Env, CurrencyCode);
	const FScopedJavaObject<jobject> PriceBigDecimal = BrazeConversions::ToJavaBigDecimal(Price);
	
	const jmethodID MethodLogPurchase = FJavaWrapper::FindMethod(Env, ClassAppboy, "logPurchase", "(Ljava/lang/String;Ljava/lang/String;Ljava/math/BigDecimal;I)V", false);
	FJavaWrapper::CallVoidMethod(Env, *AppboyInstance, MethodLogPurchase, *ProductIdentifierString, *CurrencyCodeString, *PriceBigDecimal, static_cast<int32>(Quantity));
}

void UBrazeAndroid::LogPurchaseWithProperties(const FString& ProductIdentifier, const FString& CurrencyCode, const FString& Price, const uint8 Quantity, const FBrazeProperties& Properties)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jobject> AppboyInstance = GetAppboyInstance();
	const jclass ClassAppboy = FAndroidApplication::FindJavaClass("com/appboy/Appboy");

	const FScopedJavaObject<jstring> ProductIdentifierString = FJavaHelper::ToJavaString(Env, ProductIdentifier);
	const FScopedJavaObject<jstring> CurrencyCodeString = FJavaHelper::ToJavaString(Env, CurrencyCode);
	const FScopedJavaObject<jobject> PriceBigDecimal = BrazeConversions::ToJavaBigDecimal(Price);
	const FScopedJavaObject<jobject> PropertiesObject = BrazeConversions::ToJavaAppboyProperties(Properties);

	const jmethodID MethodLogPurchase = FJavaWrapper::FindMethod(Env, ClassAppboy, "logPurchase", "(Ljava/lang/String;Ljava/lang/String;Ljava/math/BigDecimal;ILcom/appboy/models/outgoing/AppboyProperties;)V", false);
	FJavaWrapper::CallVoidMethod(Env, *AppboyInstance, MethodLogPurchase, *ProductIdentifierString, *CurrencyCodeString, *PriceBigDecimal, static_cast<int32>(Quantity), *PropertiesObject);
}

void UBrazeAndroid::RequestImmediateDataFlush()
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jobject> AppboyInstance = GetAppboyInstance();
	const jclass ClassAppboy = FAndroidApplication::FindJavaClass("com/appboy/Appboy");

	const jmethodID MethodRequestImmediateDataFlush = FJavaWrapper::FindMethod(Env, ClassAppboy, "requestImmediateDataFlush", "()V", false);
	FJavaWrapper::CallVoidMethod(Env, *AppboyInstance, MethodRequestImmediateDataFlush);
}

UBrazeUser* UBrazeAndroid::GetCurrentUser() const
{
	const FScopedJavaObject<jobject> AppboyInstance = GetAppboyInstance();
	UBrazeUserAndroid* NewUser = NewObject<UBrazeUserAndroid>();
	NewUser->Initialize(*AppboyInstance);
	return NewUser;
}

#endif 
