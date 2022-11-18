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
	const jclass ClassBrazeConfigBuilder = FAndroidApplication::FindJavaClass("com/braze/configuration/BrazeConfig$Builder");
	const jmethodID MethodSetApiKey = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setApiKey", "(Ljava/lang/String;)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetDefaultNotificationChannelName = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setDefaultNotificationChannelName", "(Ljava/lang/String;)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetDefaultNotificationChannelDescription = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setDefaultNotificationChannelDescription", "(Ljava/lang/String;)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetNewsfeedVisualIndicatorOn = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setNewsfeedVisualIndicatorOn", "(Z)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetCustomEndpoint = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setCustomEndpoint", "(Ljava/lang/String;)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetSessionTimeout = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setSessionTimeout", "(I)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetDefaultNotificationAccentColor = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setDefaultNotificationAccentColor", "(I)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetTriggerActionMinimumTimeIntervalSeconds = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setTriggerActionMinimumTimeIntervalSeconds", "(I)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetAdmMessagingRegistrationEnabled = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setAdmMessagingRegistrationEnabled", "(Z)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetIsLocationCollectionEnabled = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setIsLocationCollectionEnabled", "(Z)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetBadNetworkDataFlushInterval = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setBadNetworkDataFlushInterval", "(I)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetGoodNetworkDataFlushInterval = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setGoodNetworkDataFlushInterval", "(I)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetGreatNetworkDataFlushInterval = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setGreatNetworkDataFlushInterval", "(I)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetIsSessionStartBasedTimeoutEnabled = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setIsSessionStartBasedTimeoutEnabled", "(Z)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetIsFirebaseCloudMessagingRegistrationEnabled = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setIsFirebaseCloudMessagingRegistrationEnabled", "(Z)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetFirebaseCloudMessagingSenderIdKey = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setFirebaseCloudMessagingSenderIdKey", "(Ljava/lang/String;)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetContentCardsUnreadVisualIndicatorEnabled = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setContentCardsUnreadVisualIndicatorEnabled", "(Z)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetIsInAppMessageAccessibilityExclusiveModeEnabled = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setIsInAppMessageAccessibilityExclusiveModeEnabled", "(Z)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetIsPushWakeScreenForNotificationEnabled = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setIsPushWakeScreenForNotificationEnabled", "(Z)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetPushHtmlRenderingEnabled = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setPushHtmlRenderingEnabled", "(Z)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetGeofencesEnabled = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setGeofencesEnabled", "(Z)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetInAppMessageTestPushEagerDisplayEnabled = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setInAppMessageTestPushEagerDisplayEnabled", "(Z)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetAutomaticGeofenceRequestsEnabled = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setAutomaticGeofenceRequestsEnabled", "(Z)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodSetHandlePushDeepLinksAutomatically = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setHandlePushDeepLinksAutomatically", "(Z)Lcom/braze/configuration/BrazeConfig$Builder;", false);
    const jmethodID MethodSetSdkMetadata = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "setSdkMetadata", "(Ljava/util/EnumSet;)Lcom/braze/configuration/BrazeConfig$Builder;", false);
	const jmethodID MethodBuild = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "build", "()Lcom/braze/configuration/BrazeConfig;", false);
	
	// begin building from config
	const jmethodID MethodInitBuilder = FJavaWrapper::FindMethod(Env, ClassBrazeConfigBuilder, "<init>", "()V", false);
	const FScopedJavaObject<jobject> Builder = NewScopedJavaObject(Env, Env->NewObject(ClassBrazeConfigBuilder, MethodInitBuilder));
	
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

    // Set SDK Metadata
    const jclass ClassEnumSet = Env->FindClass("java/util/EnumSet");
    const jmethodID MethodEnumSetOf = FJavaWrapper::FindStaticMethod(Env, ClassEnumSet, "of", "(Ljava/lang/Enum;)Ljava/util/EnumSet;", false);
    FScopedJavaObject<jobject> SdkMetadataEnumField = BrazeConversions::GetEnumFieldJavaObject("com/braze/enums/BrazeSdkMetadata", "UNREAL");
    const FScopedJavaObject<jobject> SdkMetadataEnumSet(Env, Env->CallStaticObjectMethod(ClassEnumSet, MethodEnumSetOf, *SdkMetadataEnumField));
    Env->DeleteLocalRef(FJavaWrapper::CallObjectMethod(Env, *Builder, MethodSetSdkMetadata, *SdkMetadataEnumSet));
	
	// build the BrazeConfig object
	const FScopedJavaObject<jobject> BrazeConfig = NewScopedJavaObject(Env, FJavaWrapper::CallObjectMethod(Env, *Builder, MethodBuild));
	
	const jclass ClassBraze = FAndroidApplication::FindJavaClass("com/braze/Braze");
	const jmethodID MethodConfigure = FJavaWrapper::FindStaticMethod(Env, ClassBraze, "configure", "(Landroid/content/Context;Lcom/braze/configuration/BrazeConfig;)Z", false);
	Env->CallStaticBooleanMethod(ClassBraze, MethodConfigure, ApplicationContext, *BrazeConfig);

	// register lifecycle callbacks listener
	const jclass ClassBrazeActivityLifecycleCallbackListener = FAndroidApplication::FindJavaClass("com/braze.BrazeActivityLifecycleCallbackListener");
	const jmethodID MethodInitBrazeActivityLifecycleCallbackListener = FJavaWrapper::FindMethod(Env, ClassBrazeActivityLifecycleCallbackListener, "<init>", "()V", false);
	const FScopedJavaObject<jobject> BrazeActivityLifecycleCallbackListener = NewScopedJavaObject(Env, Env->NewObject(ClassBrazeActivityLifecycleCallbackListener, MethodInitBrazeActivityLifecycleCallbackListener));
	const jmethodID MethodRegisterActivityLifecycleCallbacks = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "registerActivityLifecycleCallbacks", "(Landroid/app/Application$ActivityLifecycleCallbacks;)V", false);
	FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, MethodRegisterActivityLifecycleCallbacks, *BrazeActivityLifecycleCallbackListener);

	return true;
}

FScopedJavaObject<jobject> UBrazeAndroid::GetBrazeInstance() const
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const jclass ClassBraze = FAndroidApplication::FindJavaClass("com/braze/Braze");

	const jmethodID MethodGetInstance = Env->GetStaticMethodID(ClassBraze, "getInstance", "(Landroid/content/Context;)Lcom/braze/Braze;");
	return FScopedJavaObject<jobject>(Env, Env->CallStaticObjectMethod(ClassBraze, MethodGetInstance, ApplicationContext));
}

void UBrazeAndroid::ChangeUser(const FString& UserId)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jobject> BrazeInstance = GetBrazeInstance();
	const jclass ClassBraze = FAndroidApplication::FindJavaClass("com/braze/Braze");

	const FScopedJavaObject<jstring> UserIdString = FJavaHelper::ToJavaString(Env, UserId);
	const jmethodID MethodChangeUser = FJavaWrapper::FindMethod(Env, ClassBraze, "changeUser", "(Ljava/lang/String;)V", false);
	FJavaWrapper::CallVoidMethod(Env, *BrazeInstance, MethodChangeUser, *UserIdString);
}

void UBrazeAndroid::LogCustomEvent(const FString& EventName)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jobject> BrazeInstance = GetBrazeInstance();
	const jclass ClassBraze = FAndroidApplication::FindJavaClass("com/braze/Braze");

	const FScopedJavaObject<jstring> EventString = FJavaHelper::ToJavaString(Env, EventName);
	const jmethodID MethodLogCustomEvent = FJavaWrapper::FindMethod(Env, ClassBraze, "logCustomEvent", "(Ljava/lang/String;)V", false);
	FJavaWrapper::CallVoidMethod(Env, *BrazeInstance, MethodLogCustomEvent, *EventString);
}

void UBrazeAndroid::LogCustomEventWithProperties(const FString& EventName, const FBrazeProperties& Properties)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();

	const FScopedJavaObject<jobject> BrazeInstance = GetBrazeInstance();
	const jclass ClassBraze = FAndroidApplication::FindJavaClass("com/braze/Braze");
	
	const FScopedJavaObject<jstring> EventString = FJavaHelper::ToJavaString(Env, EventName);
	const FScopedJavaObject<jobject> BrazePropertiesInstance = BrazeConversions::ToJavaBrazeProperties(Properties);
	
	const jmethodID MethodLogCustomEvent = FJavaWrapper::FindMethod(Env, ClassBraze, "logCustomEvent", "(Ljava/lang/String;Lcom/braze/models/outgoing/BrazeProperties;)V", false);
	FJavaWrapper::CallVoidMethod(Env, *BrazeInstance, MethodLogCustomEvent, *EventString, *BrazePropertiesInstance);
}

void UBrazeAndroid::LogPurchase(const FString& ProductIdentifier, const FString& CurrencyCode, const FString& Price, const uint8 Quantity)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jobject> BrazeInstance = GetBrazeInstance();
	const jclass ClassBraze = FAndroidApplication::FindJavaClass("com/braze/Braze");

	const FScopedJavaObject<jstring> ProductIdentifierString = FJavaHelper::ToJavaString(Env, ProductIdentifier);
	const FScopedJavaObject<jstring> CurrencyCodeString = FJavaHelper::ToJavaString(Env, CurrencyCode);
	const FScopedJavaObject<jobject> PriceBigDecimal = BrazeConversions::ToJavaBigDecimal(Price);
	
	const jmethodID MethodLogPurchase = FJavaWrapper::FindMethod(Env, ClassBraze, "logPurchase", "(Ljava/lang/String;Ljava/lang/String;Ljava/math/BigDecimal;I)V", false);
	FJavaWrapper::CallVoidMethod(Env, *BrazeInstance, MethodLogPurchase, *ProductIdentifierString, *CurrencyCodeString, *PriceBigDecimal, static_cast<int32>(Quantity));
}

void UBrazeAndroid::LogPurchaseWithProperties(const FString& ProductIdentifier, const FString& CurrencyCode, const FString& Price, const uint8 Quantity, const FBrazeProperties& Properties)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jobject> BrazeInstance = GetBrazeInstance();
	const jclass ClassBraze = FAndroidApplication::FindJavaClass("com/braze/Braze");

	const FScopedJavaObject<jstring> ProductIdentifierString = FJavaHelper::ToJavaString(Env, ProductIdentifier);
	const FScopedJavaObject<jstring> CurrencyCodeString = FJavaHelper::ToJavaString(Env, CurrencyCode);
	const FScopedJavaObject<jobject> PriceBigDecimal = BrazeConversions::ToJavaBigDecimal(Price);
	const FScopedJavaObject<jobject> PropertiesObject = BrazeConversions::ToJavaBrazeProperties(Properties);

	const jmethodID MethodLogPurchase = FJavaWrapper::FindMethod(Env, ClassBraze, "logPurchase", "(Ljava/lang/String;Ljava/lang/String;Ljava/math/BigDecimal;ILcom/braze/models/outgoing/BrazeProperties;)V", false);
	FJavaWrapper::CallVoidMethod(Env, *BrazeInstance, MethodLogPurchase, *ProductIdentifierString, *CurrencyCodeString, *PriceBigDecimal, static_cast<int32>(Quantity), *PropertiesObject);
}

void UBrazeAndroid::RequestImmediateDataFlush()
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jobject> BrazeInstance = GetBrazeInstance();
	const jclass ClassBraze = FAndroidApplication::FindJavaClass("com/braze/Braze");

	const jmethodID MethodRequestImmediateDataFlush = FJavaWrapper::FindMethod(Env, ClassBraze, "requestImmediateDataFlush", "()V", false);
	FJavaWrapper::CallVoidMethod(Env, *BrazeInstance, MethodRequestImmediateDataFlush);
}

UBrazeUser* UBrazeAndroid::GetCurrentUser() const
{
	const FScopedJavaObject<jobject> BrazeInstance = GetBrazeInstance();
	UBrazeUserAndroid* NewUser = NewObject<UBrazeUserAndroid>();
	NewUser->Initialize(*BrazeInstance);
	return NewUser;
}

#endif 
