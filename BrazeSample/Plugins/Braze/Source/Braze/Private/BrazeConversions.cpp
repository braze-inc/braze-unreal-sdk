// Copyright Braze Inc. All Rights Reserved.

#include "BrazeConversions.h"
#include "BrazeAttributionData.h"
#include "BrazeModule.h"

namespace BrazeConversions 
{
#if PLATFORM_IOS
	NSString* FStringToNSString(const FString& String)
	{
		return [NSString stringWithUTF8String: TCHAR_TO_ANSI(*String)];
	}

	NSDate* FDateTimeToNSDate(const FDateTime& DateTime)
	{
		NSDateComponents* DateComponents = [[NSDateComponents alloc] init];
		NSCalendar* Calendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSCalendarIdentifierGregorian];
		[DateComponents setDay: DateTime.GetDay()];
		[DateComponents setMonth: DateTime.GetMonth()];
		[DateComponents setYear: DateTime.GetYear()];
		[DateComponents setHour: DateTime.GetHour()];
		[DateComponents setMinute: DateTime.GetMinute()];
		[DateComponents setSecond: DateTime.GetSecond()];

		NSDate* Date = [Calendar dateFromComponents: DateComponents];

		[Calendar release];
		[DateComponents release];

		return Date;
	}

	NSArray* StringArrayToNSArray(const TArray<FString>& Strings)
	{
		NSMutableArray* NewArray = [[[NSMutableArray alloc] init] autorelease];

		for (const auto& Elem : Strings)
		{
			[NewArray addObject: BrazeConversions::FStringToNSString(Elem)];
		}

		return NewArray;
	}

	NSDecimalNumber* FStringToNSDecimalNumber(const FString& String)
	{
		return [NSDecimalNumber decimalNumberWithString: BrazeConversions::FStringToNSString(String)];
	}

	NSDictionary* FBrazePropertiesToNSDictionary(const FBrazeProperties& Properties)
	{
		NSMutableDictionary* NewDictionary = [[[NSMutableDictionary alloc] init] autorelease];

		for (const auto& Elem : Properties.Properties)
		{
			NSString* KeyString = BrazeConversions::FStringToNSString(Elem.Key);
			const FBrazeAny& Any = Elem.Value;
			switch (Any.Type)
			{
				case EBrazeAnyType::Int:
				{
					NewDictionary[KeyString] = [NSNumber numberWithInt: Any.IntValue];
				}
				break;
				case EBrazeAnyType::Float:
				{
					NewDictionary[KeyString] = [NSNumber numberWithFloat: Any.FloatValue];
				}
				break;
				case EBrazeAnyType::Boolean:
				{
					NewDictionary[KeyString] = [NSNumber numberWithBool: Any.BooleanValue];
				}
				break;
				case EBrazeAnyType::String:
				{
					NewDictionary[KeyString] = BrazeConversions::FStringToNSString(Any.StringValue);
				} 
				break;
				case EBrazeAnyType::Date:
				{
					NewDictionary[KeyString] = BrazeConversions::FDateTimeToNSDate(Any.DateValue);
				} 
				break;
			}	
		}

		return NewDictionary;
	}

#elif PLATFORM_ANDROID
    FScopedJavaObject<jobject> GetEnumFieldJavaObject(const FString EnumClassName, const FString FieldName)
    {
        JNIEnv* const Env = FAndroidApplication::GetJavaEnv();

        const jclass EnumClass = FAndroidApplication::FindJavaClass(TCHAR_TO_ANSI(*EnumClassName));
        FString EnumClassSignature("L");
        EnumClassSignature += EnumClassName + ";";
        const jfieldID EnumField = Env->GetStaticFieldID(EnumClass, TCHAR_TO_ANSI(*FieldName), TCHAR_TO_ANSI(*EnumClassSignature));
        return FScopedJavaObject<jobject>(Env, Env->GetStaticObjectField(EnumClass, EnumField));
    }

	FScopedJavaObject<jobject> EBrazeGenderToJObject(EBrazeGender Gender)
	{
		const ANSICHAR* FieldName = nullptr;
		switch (Gender) 
		{
			case EBrazeGender::Male: FieldName = "MALE"; break;
			case EBrazeGender::Female: FieldName = "FEMALE"; break;
			case EBrazeGender::NotApplicable: FieldName = "NOT_APPLICABLE"; break;
			case EBrazeGender::Other: FieldName = "OTHER"; break;
			case EBrazeGender::PreferNotToSay: FieldName = "PREFER_NOT_TO_SAY"; break;
			case EBrazeGender::Unknown: FieldName = "UNKNOWN"; break;
		}
		check(FieldName != nullptr);

		JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
		const jclass EnumGender = FAndroidApplication::FindJavaClass("com/braze/enums/Gender");
		const jfieldID EnumField = Env->GetStaticFieldID(EnumGender, FieldName, "Lcom/braze/enums/Gender;");
		return FScopedJavaObject<jobject>(Env, Env->GetStaticObjectField(EnumGender, EnumField));
	}

	FScopedJavaObject<jobject> EBrazeMonthToJObject(EBrazeMonth Month)
	{
		const ANSICHAR* FieldName = nullptr;
		switch (Month)
		{
			case EBrazeMonth::January: FieldName = "JANUARY"; break;
			case EBrazeMonth::February: FieldName = "FEBRUARY"; break;
			case EBrazeMonth::March: FieldName = "MARCH"; break;
			case EBrazeMonth::April: FieldName = "APRIL"; break;
			case EBrazeMonth::May: FieldName = "MAY"; break;
			case EBrazeMonth::June: FieldName = "JUNE"; break;
			case EBrazeMonth::July: FieldName = "JULY"; break;
			case EBrazeMonth::August: FieldName = "AUGUST"; break;
			case EBrazeMonth::September: FieldName = "SEPTEMBER"; break;
			case EBrazeMonth::October: FieldName = "OCTOBER"; break;
			case EBrazeMonth::November: FieldName = "NOVEMBER"; break;
			case EBrazeMonth::December: FieldName = "DECEMBER"; break;
		}
		check(FieldName != nullptr);

		JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
		const jclass EnumMonth = FAndroidApplication::FindJavaClass("com/braze/enums/Month");
		const jfieldID EnumField = Env->GetStaticFieldID(EnumMonth, FieldName, "Lcom/braze/enums/Month;");
		return FScopedJavaObject<jobject>(Env, Env->GetStaticObjectField(EnumMonth, EnumField));
	}

	FScopedJavaObject<jobject> EBrazeNotificationSubscriptionTypeToJObject(EBrazeNotificationSubscriptionType NotificationSubscriptionType)
	{
		const ANSICHAR* FieldName = nullptr;
		switch (NotificationSubscriptionType) 
		{
			case EBrazeNotificationSubscriptionType::OptedIn: FieldName = "OPTED_IN"; break;
			case EBrazeNotificationSubscriptionType::Subscribed: FieldName = "SUBSCRIBED"; break;
			case EBrazeNotificationSubscriptionType::Unsubscribed: FieldName = "UNSUBSCRIBED"; break;
		}
		check(FieldName != nullptr);

		JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
		const jclass EnumNotificationSubscriptionType = FAndroidApplication::FindJavaClass("com/braze/enums/NotificationSubscriptionType");
		const jfieldID EnumField = Env->GetStaticFieldID(EnumNotificationSubscriptionType, FieldName, "Lcom/braze/enums/NotificationSubscriptionType;");
		return FScopedJavaObject<jobject>(Env, Env->GetStaticObjectField(EnumNotificationSubscriptionType, EnumField));
	}

	FScopedJavaObject<jobject> AttributionDataToJObject(const FBrazeAttributionData& AttributionData)
	{
		JNIEnv* const Env = FAndroidApplication::GetJavaEnv();

		const jclass ClassAttributionData = FAndroidApplication::FindJavaClass("com/braze/models/outgoing/AttributionData");
		const jmethodID MethodInitAttributionData = FJavaWrapper::FindMethod(Env, ClassAttributionData, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", false);

		return FScopedJavaObject<jobject>(Env, Env->NewObject(ClassAttributionData, MethodInitAttributionData, *FJavaHelper::ToJavaString(Env, AttributionData.Network),
		                                                                                                       *FJavaHelper::ToJavaString(Env, AttributionData.Campaign),
																											   *FJavaHelper::ToJavaString(Env, AttributionData.AdGroup),
																											   *FJavaHelper::ToJavaString(Env, AttributionData.Creative)));
	}

	FScopedJavaObject<jobjectArray> StringArrayToJObjectArray(const TArray<FString>& Strings)
	{
		JNIEnv* const Env = FAndroidApplication::GetJavaEnv();

		const jclass ClassString = Env->FindClass("java/lang/String");
		const jobjectArray StringArray = Env->NewObjectArray(Strings.Num(), ClassString, nullptr);
		
		for (int32 Index = 0, Num = Strings.Num(); Index < Num; ++Index)
		{
			Env->SetObjectArrayElement(StringArray, Index, *FJavaHelper::ToJavaString(Env, Strings[Index]));
		}

		return FScopedJavaObject<jobjectArray>(Env, StringArray);
	}

	FScopedJavaObject<jobject> ToJavaBigDecimal(const FString& DecimalString)
	{
		JNIEnv* const Env = FAndroidApplication::GetJavaEnv();
		
		const jclass ClassBigDecimal = Env->FindClass("java/math/BigDecimal");
		const jmethodID MethodInitBigDecimal = FJavaWrapper::FindMethod(Env, ClassBigDecimal, "<init>", "(Ljava/lang/String;)V", false);
		const jobject BigDecimalInstance = Env->NewObject(ClassBigDecimal, MethodInitBigDecimal, *FJavaHelper::ToJavaString(Env, DecimalString));

		return FScopedJavaObject<jobject>(Env, BigDecimalInstance);
	}

	FScopedJavaObject<jobject> ToJavaDate(const FDateTime& DateTime)
	{
		JNIEnv* const Env = FAndroidApplication::GetJavaEnv();

		const jclass ClassDate = Env->FindClass("java/util/Date");
		const jmethodID MethodInitDate = FJavaWrapper::FindMethod(Env, ClassDate, "<init>", "(J)V", false);
		const jobject DateInstance = Env->NewObject(ClassDate, MethodInitDate, DateTime.ToUnixTimestamp());

		return FScopedJavaObject<jobject>(Env, DateInstance);
	}	

	FScopedJavaObject<jobject> ToJavaBrazeProperties(const FBrazeProperties& Properties)
	{
		JNIEnv* const Env = FAndroidApplication::GetJavaEnv();

		const jclass ClassBrazeProperties = FAndroidApplication::FindJavaClass("com/braze/models/outgoing/BrazeProperties");
		const jmethodID MethodInitBrazeProperties = FJavaWrapper::FindMethod(Env, ClassBrazeProperties, "<init>", "()V", false);
		const jobject BrazePropertiesInstance = Env->NewObject(ClassBrazeProperties, MethodInitBrazeProperties, FJavaWrapper::GameActivityThis);

		const jmethodID MethodAddProperty = FJavaWrapper::FindMethod(Env, ClassBrazeProperties, "addProperty", "(Ljava/lang/String;Ljava/lang/Object;)Lcom/braze/models/outgoing/BrazeProperties;", false);

		for (const auto& Elem : Properties.Properties)
		{
			const FScopedJavaObject<jstring> KeyString = FJavaHelper::ToJavaString(Env, Elem.Key);
			const FBrazeAny& Any = Elem.Value;

			switch (Any.Type)
			{
				case EBrazeAnyType::Int:
				{
                    const jclass ClassInt = Env->FindClass("java/lang/Integer");
                    const jmethodID MethodInitInt = FJavaWrapper::FindMethod(Env, ClassInt, "<init>", "(I)V", false);
                    const jobject IntInstance = Env->NewObject(ClassInt, MethodInitInt, Any.IntValue);
					const FScopedJavaObject<jobject> RetVal(Env, FJavaWrapper::CallObjectMethod(Env, BrazePropertiesInstance, MethodAddProperty, *KeyString, IntInstance));
				}
				break;
				case EBrazeAnyType::Float:
				{
                    const jclass ClassFloat = Env->FindClass("java/lang/Float");
                    const jmethodID ClassInitFloat = FJavaWrapper::FindMethod(Env, ClassFloat, "<init>", "(F)V", false);
                    const jobject FloatInstance = Env->NewObject(ClassFloat, ClassInitFloat, Any.FloatValue);
                    const FScopedJavaObject<jobject> RetVal(Env, FJavaWrapper::CallObjectMethod(Env, BrazePropertiesInstance, MethodAddProperty, *KeyString, FloatInstance));
				}
				break;
				case EBrazeAnyType::Boolean:
				{
                    const jclass ClassBoolean = Env->FindClass("java/lang/Boolean");
                    const jmethodID ClassInitBoolean = FJavaWrapper::FindMethod(Env, ClassBoolean, "<init>", "(Z)V", false);
                    const jobject BooleanInstance = Env->NewObject(ClassBoolean, ClassInitBoolean, Any.BooleanValue);
					const FScopedJavaObject<jobject> RetVal(Env, FJavaWrapper::CallObjectMethod(Env, BrazePropertiesInstance, MethodAddProperty, *KeyString, BooleanInstance));
				}
				break;
				case EBrazeAnyType::String:
				{
					const FScopedJavaObject<jobject> RetVal(Env, FJavaWrapper::CallObjectMethod(Env, BrazePropertiesInstance, MethodAddProperty, *KeyString, *FJavaHelper::ToJavaString(Env, Any.StringValue)));
				} 
				break;
				case EBrazeAnyType::Date:
				{
					const FScopedJavaObject<jobject> RetVal(Env, FJavaWrapper::CallObjectMethod(Env, BrazePropertiesInstance, MethodAddProperty, *KeyString, *BrazeConversions::ToJavaDate(Any.DateValue)));
				} 
				break;
			}
		}

		return FScopedJavaObject<jobject>(Env, BrazePropertiesInstance);
	}

#endif 
}
