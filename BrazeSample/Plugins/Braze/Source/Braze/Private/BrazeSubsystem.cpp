// Copyright Braze Inc. All Rights Reserved.

#include "BrazeSubsystem.h"
#include "BrazeConfig.h"
#include "BrazeModule.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/BrazeAndroid.h"
#elif PLATFORM_IOS
#include "IOS/BrazeIOS.h"
#import "IOS/AppboySDK/Appboy.h"
#endif

void UBrazeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    const UBrazeConfig* const Config = UBrazeConfig::StaticClass()->GetDefaultObject<UBrazeConfig>();
    if (!ensure(IsValid(Config)))
    {
		UE_LOG(LogBraze, Error, TEXT("%s - Can't initialize invalid config"), *GetName());
		return;
    }

	if (Config->bAutoInitialize)
	{
		InitializeBraze(Config);
	}
}

UBraze* UBrazeSubsystem::InitializeBraze(const UBrazeConfig* Config)
{
	if (IsValid(BrazeInstance))
	{
		UE_LOG(LogBraze, Log, TEXT("%s - Braze already initialized, returning initialized instance (config ignored)."), *GetName());
		return BrazeInstance;
	}

#if PLATFORM_ANDROID
	BrazeInstance = NewObject<UBrazeAndroid>();
#elif PLATFORM_IOS
	BrazeInstance = NewObject<UBrazeIOS>();
#endif

	if (IsValid(BrazeInstance))
	{
		UE_LOG(LogBraze, Log, TEXT("Initializing Braze."));

		if (!IsValid(Config)) 
		{
			Config = UBrazeConfig::StaticClass()->GetDefaultObject<UBrazeConfig>();
		}

		if (!BrazeInstance->Init(*Config))
		{
			BrazeInstance = nullptr;
		}

	}

	return BrazeInstance;
}

void UBrazeSubsystem::AndroidSetLogLevel(EBrazeLogLevel BrazeLogLevel)
{
#if PLATFORM_ANDROID
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const jclass ClassBrazeLogger = FAndroidApplication::FindJavaClass("com/braze/support/BrazeLogger");
	const jmethodID MethodSetLogLevel = Env->GetStaticMethodID(ClassBrazeLogger, "setLogLevel", "(I)V");

	int32 Level = static_cast<int32>(BrazeLogLevel);
	if (BrazeLogLevel == EBrazeLogLevel::Suppress)
	{
		// BP Enum types are only uint8, but the value for suppress is 2147483647
		Level = 2147483647;
	}

	Env->CallStaticVoidMethod(ClassBrazeLogger, MethodSetLogLevel, static_cast<int32>(Level));
#endif 
}


void UBrazeSubsystem::EnableSDK()
{
#if PLATFORM_ANDROID
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const jclass ClassBraze = FAndroidApplication::FindJavaClass("com/braze/Braze");
	
	const jmethodID MethodGetApplicationContext = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "getApplicationContext", "()Landroid/content/Context;", false);
	const FScopedJavaObject<jobject> ApplicationContext = NewScopedJavaObject(Env, FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, MethodGetApplicationContext));

	const jmethodID MethodEnableSDK = Env->GetStaticMethodID(ClassBraze, "enableSdk", "(Landroid/content/Context;)V");
	Env->CallStaticVoidMethod(ClassBraze, MethodEnableSDK, *ApplicationContext);
#elif PLATFORM_IOS 
	dispatch_sync(dispatch_get_main_queue(), ^{
		[Appboy requestEnableSDKOnNextAppRun];
	});
#endif
}

void UBrazeSubsystem::DisableSDK()
{
#if PLATFORM_ANDROID
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const jclass ClassBraze = FAndroidApplication::FindJavaClass("com/braze/Braze");

	const jmethodID MethodGetApplicationContext = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "getApplicationContext", "()Landroid/content/Context;", false);
	const FScopedJavaObject<jobject> ApplicationContext = NewScopedJavaObject(Env, FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, MethodGetApplicationContext));

	const jmethodID MethodDisableSDK = Env->GetStaticMethodID(ClassBraze, "disableSdk", "(Landroid/content/Context;)V");
	Env->CallStaticVoidMethod(ClassBraze, MethodDisableSDK, *ApplicationContext);
#elif PLATFORM_IOS 
	dispatch_sync(dispatch_get_main_queue(), ^{
		[Appboy disableSDK];
	});
#endif

	BrazeInstance = nullptr;
}

void UBrazeSubsystem::WipeData()
{
#if PLATFORM_ANDROID
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const jclass ClassBraze = FAndroidApplication::FindJavaClass("com/braze/Braze");

	const jmethodID MethodGetApplicationContext = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "getApplicationContext", "()Landroid/content/Context;", false);
	const FScopedJavaObject<jobject> ApplicationContext = NewScopedJavaObject(Env, FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, MethodGetApplicationContext));

	const jmethodID MethodWipeData = Env->GetStaticMethodID(ClassBraze, "wipeData", "(Landroid/content/Context;)V");
	Env->CallStaticVoidMethod(ClassBraze, MethodWipeData, *ApplicationContext);
#elif PLATFORM_IOS

	dispatch_sync(dispatch_get_main_queue(), ^{
		[Appboy wipeDataAndDisableForAppRun];
	});
	
#endif
	
	BrazeInstance = nullptr;
}