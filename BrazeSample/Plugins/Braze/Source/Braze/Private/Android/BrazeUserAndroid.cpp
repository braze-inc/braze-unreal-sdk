// Copyright Braze Inc. All Rights Reserved.

#include "BrazeUserAndroid.h"
#include "BrazeModule.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "BrazeConversions.h"

namespace {
	template <typename ValueType>
	bool CallSetCustomUserAttributesWithParams(const jobject& BrazeUser, const ANSICHAR* Signature, const FString& AttributeKey, const ValueType& Value)
	{
		JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
		const FScopedJavaObject<jstring> AttributeKeyString = FJavaHelper::ToJavaString(Env, AttributeKey);

		const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
		const jmethodID MethodSetCustomUserAttribute = FJavaWrapper::FindMethod(Env, ClassBrazeUser, "setCustomUserAttribute", Signature, false);

		return FJavaWrapper::CallBooleanMethod(Env, BrazeUser, MethodSetCustomUserAttribute, *AttributeKeyString, Value);
	}

	template <>
	bool CallSetCustomUserAttributesWithParams(const jobject& BrazeUser, const ANSICHAR* Signature, const FString& AttributeKey, const FString& Value)
	{
		JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
		const FScopedJavaObject<jstring> AttributeKeyString = FJavaHelper::ToJavaString(Env, AttributeKey);
		const FScopedJavaObject<jstring> ValueString = FJavaHelper::ToJavaString(Env, Value);

		const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
		const jmethodID MethodSetCustomUserAttribute = FJavaWrapper::FindMethod(Env, ClassBrazeUser, "setCustomUserAttribute", Signature, false);
		
		return FJavaWrapper::CallBooleanMethod(Env, BrazeUser, MethodSetCustomUserAttribute, *AttributeKeyString, *ValueString);
	}

	bool CallUserProfileMethodWithStringParam(const jobject& BrazeUser, const ANSICHAR* MethodName, const FString& Param)
	{
		JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
		const FScopedJavaObject<jstring> ParamString = FJavaHelper::ToJavaString(Env, Param);

		const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
		const jmethodID Method = FJavaWrapper::FindMethod(Env, ClassBrazeUser, MethodName, "(Ljava/lang/String;)Z", false);

		return FJavaWrapper::CallBooleanMethod(Env, BrazeUser, Method, *ParamString);
	}
}

void UBrazeUserAndroid::BeginDestroy()
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	if (Env != nullptr && UserJObject != nullptr)
	{
		Env->DeleteLocalRef(UserJObject);
	}

	Super::BeginDestroy();
}

bool UBrazeUserAndroid::AddAlias(const FString& Alias, const FString& Label)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jstring> AliasString = FJavaHelper::ToJavaString(Env, Alias);
	const FScopedJavaObject<jstring> LabelString = FJavaHelper::ToJavaString(Env, Label);

	const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
	const jmethodID MethodAddAlias = FJavaWrapper::FindMethod(Env, ClassBrazeUser, "addAlias", "(Ljava/lang/String;Ljava/lang/String;)Z", false);
	
	return FJavaWrapper::CallBooleanMethod(Env, UserJObject, MethodAddAlias, *AliasString, *LabelString);
}

bool UBrazeUserAndroid::SetCustomUserAttributeString(const FString& AttributeKey, const FString& Value)
{
	return CallSetCustomUserAttributesWithParams(UserJObject, "(Ljava/lang/String;Ljava/lang/String;)Z", AttributeKey, Value);
}

bool UBrazeUserAndroid::SetCustomUserAttributeInt(const FString& AttributeKey, int32 Value)
{
	return CallSetCustomUserAttributesWithParams(UserJObject, "(Ljava/lang/String;I)Z", AttributeKey, Value);
}

bool UBrazeUserAndroid::SetCustomUserAttributeLong(const FString& AttributeKey, int64 Value)
{
	return CallSetCustomUserAttributesWithParams(UserJObject, "(Ljava/lang/String;J)Z", AttributeKey, Value);
}

bool UBrazeUserAndroid::SetCustomUserAttributeFloat(const FString& AttributeKey, float Value)
{
	return CallSetCustomUserAttributesWithParams(UserJObject, "(Ljava/lang/String;F)Z", AttributeKey, Value);
}

bool UBrazeUserAndroid::SetCustomUserAttributeDouble(const FString& AttributeKey, double Value)
{
	return CallSetCustomUserAttributesWithParams(UserJObject, "(Ljava/lang/String;D)Z", AttributeKey, Value);
}

bool UBrazeUserAndroid::SetCustomUserAttributeBool(const FString& AttributeKey, bool Value)
{
	return CallSetCustomUserAttributesWithParams(UserJObject, "(Ljava/lang/String;Z)Z", AttributeKey, Value);
}

bool UBrazeUserAndroid::SetCustomUserAttributeDate(const FString& AttributeKey, const FDateTime& Date)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	
	const FScopedJavaObject<jstring> AttributeKeyString = FJavaHelper::ToJavaString(Env, AttributeKey);
	const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
	const jmethodID MethodSetCustomUserAttributeToSecondsFromEpoch = FJavaWrapper::FindMethod(Env, ClassBrazeUser, "setCustomUserAttributeToSecondsFromEpoch", "(Ljava/lang/String;J)Z", false);

	int64 UnixTimestamp = Date.ToUnixTimestamp();
	
	return FJavaWrapper::CallBooleanMethod(Env, UserJObject, MethodSetCustomUserAttributeToSecondsFromEpoch, *AttributeKeyString, UnixTimestamp);
}

bool UBrazeUserAndroid::SetCustomAttributeArray(const FString& AttributeKey, const TArray<FString>& Values)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jstring> AttributeKeyString = FJavaHelper::ToJavaString(Env, AttributeKey);
	const FScopedJavaObject<jobjectArray> ValuesArray = BrazeConversions::StringArrayToJObjectArray(Values);

	const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
	const jmethodID MethodSetCustomAttributeArray = FJavaWrapper::FindMethod(Env, ClassBrazeUser, "setCustomAttributeArray", "(Ljava/lang/String;[Ljava/lang/String;)Z", false);

	return FJavaWrapper::CallBooleanMethod(Env, UserJObject, MethodSetCustomAttributeArray, *AttributeKeyString, *ValuesArray);
}

bool UBrazeUserAndroid::UnsetCustomAttribute(const FString& AttributeKey)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jstring> AttributeKeyString = FJavaHelper::ToJavaString(Env, AttributeKey);

	const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
	const jmethodID MethodUnsetCustomAttribute = FJavaWrapper::FindMethod(Env, ClassBrazeUser, "unsetCustomUserAttribute", "(Ljava/lang/String;)Z", false);

	return FJavaWrapper::CallBooleanMethod(Env, UserJObject, MethodUnsetCustomAttribute, *AttributeKeyString);
}

bool UBrazeUserAndroid::IncrementCustomUserAttribute(const FString& AttributeKey, int32 IncrementValue)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jstring> AttributeKeyString = FJavaHelper::ToJavaString(Env, AttributeKey);

	const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
	const jmethodID MethodIncrementCustomUserAttribute = FJavaWrapper::FindMethod(Env, ClassBrazeUser, "incrementCustomUserAttribute", "(Ljava/lang/String;I)Z", false);

	return FJavaWrapper::CallBooleanMethod(Env, UserJObject, MethodIncrementCustomUserAttribute, *AttributeKeyString, IncrementValue);
}

bool UBrazeUserAndroid::AddToCustomAttributeArray(const FString& AttributeKey, const FString& Value)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jstring> AttributeKeyString = FJavaHelper::ToJavaString(Env, AttributeKey);
	const FScopedJavaObject<jstring> ValueString = FJavaHelper::ToJavaString(Env, Value);

	const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
	const jmethodID MethodAddToCustomAttributeArray = FJavaWrapper::FindMethod(Env, ClassBrazeUser, "addToCustomAttributeArray", "(Ljava/lang/String;Ljava/lang/String;)Z", false);

	return FJavaWrapper::CallBooleanMethod(Env, UserJObject, MethodAddToCustomAttributeArray, *AttributeKeyString, *ValueString);
}

bool UBrazeUserAndroid::RemoveFromCustomAttributeArray(const FString& AttributeKey, const FString& Value)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jstring> AttributeKeyString = FJavaHelper::ToJavaString(Env, AttributeKey);
	const FScopedJavaObject<jstring> ValueString = FJavaHelper::ToJavaString(Env, Value);

	const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
	const jmethodID MethodRemoveFromCustomAttributeArray = FJavaWrapper::FindMethod(Env, ClassBrazeUser, "removeFromCustomAttributeArray", "(Ljava/lang/String;Ljava/lang/String;)Z", false);

	return FJavaWrapper::CallBooleanMethod(Env, UserJObject, MethodRemoveFromCustomAttributeArray, *AttributeKeyString, *ValueString);
}

bool UBrazeUserAndroid::SetEmail(const FString& Email)
{
	return CallUserProfileMethodWithStringParam(UserJObject, "setEmail", Email);
}

bool UBrazeUserAndroid::SetFirstName(const FString& FirstName)
{
	return CallUserProfileMethodWithStringParam(UserJObject, "setFirstName", FirstName);
}

bool UBrazeUserAndroid::SetLastName(const FString& LastName)
{
	return CallUserProfileMethodWithStringParam(UserJObject, "setLastName", LastName);
}

bool UBrazeUserAndroid::SetGender(EBrazeGender Gender)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jobject> GenderValue = BrazeConversions::EBrazeGenderToJObject(Gender);

	const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
	const jmethodID MethodSetGender = FJavaWrapper::FindMethod(Env, ClassBrazeUser, "setGender", "(Lcom/braze/enums/Gender;)Z", false);

	return FJavaWrapper::CallBooleanMethod(Env, UserJObject, MethodSetGender, *GenderValue);
}

bool UBrazeUserAndroid::SetLanguage(const FString& Language)
{
	return CallUserProfileMethodWithStringParam(UserJObject, "setLanguage", Language);
}

bool UBrazeUserAndroid::SetCountry(const FString& Country)
{
	return CallUserProfileMethodWithStringParam(UserJObject, "setCountry", Country);
}

bool UBrazeUserAndroid::SetHomeCity(const FString& HomeCity)
{
	return CallUserProfileMethodWithStringParam(UserJObject, "setHomeCity", HomeCity);
}

bool UBrazeUserAndroid::SetPhoneNumber(const FString& PhoneNumber)
{
	return CallUserProfileMethodWithStringParam(UserJObject, "setPhoneNumber", PhoneNumber);
}

bool UBrazeUserAndroid::SetDateOfBirth(int32 Year, EBrazeMonth Month, int32 Day)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jobject> MonthValue = BrazeConversions::EBrazeMonthToJObject(Month);

	const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
	const jmethodID MethodSetDateOfBirth = FJavaWrapper::FindMethod(Env, ClassBrazeUser, "setDateOfBirth", "(ILcom/braze/enums/Month;I)Z", false);

	return FJavaWrapper::CallBooleanMethod(Env, UserJObject, MethodSetDateOfBirth, Year, *MonthValue, Day);
}

bool UBrazeUserAndroid::SetPushSubscriptionType(EBrazeNotificationSubscriptionType SubscriptionType)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jobject> SubscriptionTypeValue = BrazeConversions::EBrazeNotificationSubscriptionTypeToJObject(SubscriptionType);

	const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
	const jmethodID MethodSetPushSubscriptionType = FJavaWrapper::FindMethod(Env, ClassBrazeUser, "setPushNotificationSubscriptionType", "(Lcom/braze/enums/NotificationSubscriptionType;)Z", false);

	return FJavaWrapper::CallBooleanMethod(Env, UserJObject, MethodSetPushSubscriptionType, *SubscriptionTypeValue);
}

bool UBrazeUserAndroid::SetEmailSubscriptionType(EBrazeNotificationSubscriptionType SubscriptionType)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jobject> SubscriptionTypeValue = BrazeConversions::EBrazeNotificationSubscriptionTypeToJObject(SubscriptionType);

	const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
	const jmethodID MethodSetPushSubscriptionType = FJavaWrapper::FindMethod(Env, ClassBrazeUser, "setEmailNotificationSubscriptionType", "(Lcom/braze/enums/NotificationSubscriptionType;)Z", false);

	return FJavaWrapper::CallBooleanMethod(Env, UserJObject, MethodSetPushSubscriptionType, *SubscriptionTypeValue);
}

bool UBrazeUserAndroid::SetAttributionData(const FBrazeAttributionData& AttributionData)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const FScopedJavaObject<jobject> AttributionDataValue = BrazeConversions::AttributionDataToJObject(AttributionData);

	const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
	const jmethodID MethodSetAttributionData = FJavaWrapper::FindMethod(Env, ClassBrazeUser, "setAttributionData", "(Lcom/braze/models/outgoing/AttributionData;)Z", false);

	return FJavaWrapper::CallBooleanMethod(Env, UserJObject, MethodSetAttributionData, *AttributionDataValue);
}

void UBrazeUserAndroid::Initialize(const jobject& BrazeInstance)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	const jclass ClassBraze = FAndroidApplication::FindJavaClass("com/braze/Braze");
	const jmethodID MethodGetUser = FJavaWrapper::FindMethod(Env, ClassBraze, "getCurrentUser", "()Lcom/braze/BrazeUser;", false);
	UserJObject = FJavaWrapper::CallObjectMethod(Env, BrazeInstance, MethodGetUser);
}

void UBrazeUserAndroid::SetLastKnownLocation(double Latitude, double Longitude, double Altitude, double Accuracy)
{
	JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
	
	const jclass ClassBrazeUser = FAndroidApplication::FindJavaClass("com/braze/BrazeUser");
	const jmethodID MethodSetLastKnownLocation = FJavaWrapper::FindMethod(Env, ClassBrazeUser, "setLastKnownLocation", "(DDLjava/lang/Double;Ljava/lang/Double;)V", false);

	const jclass ClassDouble = Env->FindClass("java/lang/Double");
	const jmethodID MethodDoubleInit = FJavaWrapper::FindMethod(Env, ClassDouble, "<init>", "(D)V", false);
	const FScopedJavaObject<jobject> AltitudeDouble = NewScopedJavaObject(Env, Env->NewObject(ClassDouble, MethodDoubleInit, Altitude));
	const FScopedJavaObject<jobject> AccuracyDouble = NewScopedJavaObject(Env, Env->NewObject(ClassDouble, MethodDoubleInit, Accuracy));

	FJavaWrapper::CallVoidMethod(Env, UserJObject, MethodSetLastKnownLocation, Latitude, Longitude, *AltitudeDouble, *AccuracyDouble);
}

#endif
