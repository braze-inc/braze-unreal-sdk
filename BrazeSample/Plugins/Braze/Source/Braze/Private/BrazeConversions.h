// Copyright Braze Inc. All Rights Reserved.

#pragma once

#include "Braze.h"
#include "CoreMinimal.h"

struct FBrazeProperties;

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/BrazeUserAndroid.h"
#endif

struct FBrazeAttributionData;
struct FBrazeProperties;

namespace BrazeConversions 
{
#if PLATFORM_IOS
	NSString* FStringToNSString(const FString& String);
	NSDate* FDateTimeToNSDate(const FDateTime& DateTime);
	NSArray* StringArrayToNSArray(const TArray<FString>& Strings);
	NSDecimalNumber* FStringToNSDecimalNumber(const FString& String);
	NSDictionary* FBrazePropertiesToNSDictionary(const FBrazeProperties& Properties);
#elif PLATFORM_ANDROID
	FScopedJavaObject<jobject> GetEnumFieldJavaObject(const FString EnumClassName, const FString FieldName);
	FScopedJavaObject<jobject> EBrazeGenderToJObject(EBrazeGender Gender);
	FScopedJavaObject<jobject> EBrazeMonthToJObject(EBrazeMonth Month);
	FScopedJavaObject<jobject> EBrazeNotificationSubscriptionTypeToJObject(EBrazeNotificationSubscriptionType NotificationSubscriptionType);
	FScopedJavaObject<jobject> AttributionDataToJObject(const FBrazeAttributionData& AttributionData);
	FScopedJavaObject<jobjectArray> StringArrayToJObjectArray(const TArray<FString>& Strings);
	FScopedJavaObject<jobject> ToJavaBigDecimal(const FString& DecimalString);
	FScopedJavaObject<jobject> ToJavaDate(const FDateTime& DateTime);
	FScopedJavaObject<jobject> ToJavaBrazeProperties(const FBrazeProperties& Properties);

#endif
}
