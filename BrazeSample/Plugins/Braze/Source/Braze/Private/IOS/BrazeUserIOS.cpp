// Copyright Braze Inc. All Rights Reserved.

#include "BrazeUserIOS.h"
#include "BrazeModule.h"

#if PLATFORM_IOS

#include "BrazeConversions.h"
#include "BrazeAttributionData.h"
#import "IOS/AppboySDK/Appboy.h"
#import "IOS/AppboySDK/ABKUser.h"
#import "IOS/AppboySDK/ABKAttributionData.h"

bool UBrazeUserIOS::AddAlias(const FString& Alias, const FString& Label)
{
	__block BOOL RetVal = NO;
	dispatch_sync(dispatch_get_main_queue(), ^{
		RetVal = [[Appboy sharedInstance].user addAlias: BrazeConversions::FStringToNSString(Alias) withLabel: BrazeConversions::FStringToNSString(Label)];
	});
	return RetVal;
}

bool UBrazeUserIOS::SetCustomUserAttributeString(const FString& AttributeKey, const FString& Value)
{
	__block BOOL RetVal = NO;
	dispatch_sync(dispatch_get_main_queue(), ^{
		RetVal = [[Appboy sharedInstance].user setCustomAttributeWithKey: BrazeConversions::FStringToNSString(AttributeKey) andStringValue: BrazeConversions::FStringToNSString(Value)];
	});

	return RetVal;
}

bool UBrazeUserIOS::SetCustomUserAttributeInt(const FString& AttributeKey, int32 Value) 
{
	__block BOOL RetVal = NO;
	dispatch_sync(dispatch_get_main_queue(), ^{
		RetVal = [[Appboy sharedInstance].user setCustomAttributeWithKey: BrazeConversions::FStringToNSString(AttributeKey) andIntegerValue: Value];
	});

	return RetVal;
}

bool UBrazeUserIOS::SetCustomUserAttributeFloat(const FString& AttributeKey, float Value) 
{
	__block BOOL RetVal = NO;
	dispatch_sync(dispatch_get_main_queue(), ^{
		RetVal = [[Appboy sharedInstance].user setCustomAttributeWithKey: BrazeConversions::FStringToNSString(AttributeKey)  andDoubleValue: static_cast<double>(Value)];
	});

	return RetVal;
}

bool UBrazeUserIOS::SetCustomUserAttributeDouble(const FString& AttributeKey, double Value)
{
	__block BOOL RetVal = NO;
	dispatch_sync(dispatch_get_main_queue(), ^{
		RetVal = [[Appboy sharedInstance].user setCustomAttributeWithKey: BrazeConversions::FStringToNSString(AttributeKey)  andDoubleValue: Value];
	});

	return RetVal;
}

bool UBrazeUserIOS::SetCustomUserAttributeBool(const FString& AttributeKey, bool Value)
{
	__block BOOL RetVal = NO;
	dispatch_sync(dispatch_get_main_queue(), ^{
		RetVal = [[Appboy sharedInstance].user setCustomAttributeWithKey: BrazeConversions::FStringToNSString(AttributeKey)  andBOOLValue: Value];
	});

	return RetVal;
}

bool UBrazeUserIOS::SetCustomUserAttributeDate(const FString& AttributeKey, const FDateTime& Date) 
{
	__block BOOL RetVal = NO;
	dispatch_sync(dispatch_get_main_queue(), ^{
		RetVal = [[Appboy sharedInstance].user setCustomAttributeWithKey: BrazeConversions::FStringToNSString(AttributeKey) andDateValue: BrazeConversions::FDateTimeToNSDate(Date)];
	});

	return RetVal;
}

bool UBrazeUserIOS::SetCustomAttributeArray(const FString& AttributeKey, const TArray<FString>& Values)
{
	__block BOOL RetVal = NO;
	dispatch_sync(dispatch_get_main_queue(), ^{
		RetVal = [[Appboy sharedInstance].user setCustomAttributeArrayWithKey: BrazeConversions::FStringToNSString(AttributeKey) array: BrazeConversions::StringArrayToNSArray(Values)];
	});

	return RetVal;
}

bool UBrazeUserIOS::UnsetCustomAttribute(const FString& AttributeKey)
{
	__block BOOL RetVal = NO;
	dispatch_sync(dispatch_get_main_queue(), ^{
		RetVal = [[Appboy sharedInstance].user unsetCustomAttributeWithKey: BrazeConversions::FStringToNSString(AttributeKey)];
	});

	return RetVal;
}

bool UBrazeUserIOS::IncrementCustomUserAttribute(const FString& AttributeKey, int32 IncrementValue)
{
	__block BOOL RetVal = NO;
	dispatch_sync(dispatch_get_main_queue(), ^{
		RetVal = [[Appboy sharedInstance].user incrementCustomUserAttribute: BrazeConversions::FStringToNSString(AttributeKey) by: IncrementValue];
	});

	return RetVal;
}

bool UBrazeUserIOS::AddToCustomAttributeArray(const FString& AttributeKey, const FString& Value)
{
	__block BOOL RetVal = NO;
	dispatch_sync(dispatch_get_main_queue(), ^{
		RetVal = [[Appboy sharedInstance].user addToCustomAttributeArrayWithKey: BrazeConversions::FStringToNSString(AttributeKey) value: BrazeConversions::FStringToNSString(Value)];
	});

	return RetVal;
}

bool UBrazeUserIOS::RemoveFromCustomAttributeArray(const FString& AttributeKey, const FString& Value)
{
	__block BOOL RetVal = NO;
	dispatch_sync(dispatch_get_main_queue(), ^{
		RetVal = [[Appboy sharedInstance].user removeFromCustomAttributeArrayWithKey: BrazeConversions::FStringToNSString(AttributeKey) value: BrazeConversions::FStringToNSString(Value)];
	});

	return RetVal;
}

bool UBrazeUserIOS::SetEmail(const FString& Email)
{
	dispatch_sync(dispatch_get_main_queue(), ^{
		[Appboy sharedInstance].user.email = BrazeConversions::FStringToNSString(Email);
	});

	return true;
}

bool UBrazeUserIOS::SetFirstName(const FString& FirstName)
{
	dispatch_sync(dispatch_get_main_queue(), ^{
		[Appboy sharedInstance].user.firstName = BrazeConversions::FStringToNSString(FirstName);
	});

	return true;
}

bool UBrazeUserIOS::SetLastName(const FString& LastName)
{
	dispatch_sync(dispatch_get_main_queue(), ^{
		[Appboy sharedInstance].user.lastName = BrazeConversions::FStringToNSString(LastName);
	});

	return true;
}

bool UBrazeUserIOS::SetGender(EBrazeGender Gender)
{
	__block BOOL RetVal = NO;
	dispatch_sync(dispatch_get_main_queue(), ^{
		RetVal = [[Appboy sharedInstance].user setGender: static_cast<ABKUserGenderType>(Gender)];
	});

	return RetVal;
}

bool UBrazeUserIOS::SetLanguage(const FString& Language)
{
	dispatch_sync(dispatch_get_main_queue(), ^{
		[Appboy sharedInstance].user.language = BrazeConversions::FStringToNSString(Language);
	});

	return true;
}

bool UBrazeUserIOS::SetCountry(const FString& Country)
{
	dispatch_sync(dispatch_get_main_queue(), ^{
		[Appboy sharedInstance].user.country = BrazeConversions::FStringToNSString(Country);
	});

	return true;
}

bool UBrazeUserIOS::SetHomeCity(const FString& HomeCity)
{
	dispatch_sync(dispatch_get_main_queue(), ^{
		[Appboy sharedInstance].user.homeCity = BrazeConversions::FStringToNSString(HomeCity);
	});

	return true;
}

bool UBrazeUserIOS::SetPhoneNumber(const FString& PhoneNumber)
{
	dispatch_sync(dispatch_get_main_queue(), ^{
		[Appboy sharedInstance].user.phone = BrazeConversions::FStringToNSString(PhoneNumber);
	});

	return true;
}

bool UBrazeUserIOS::SetDateOfBirth(int32 Year, EBrazeMonth Month, int32 Day)
{
	dispatch_sync(dispatch_get_main_queue(), ^{
		NSDateComponents* DateComponents = [[NSDateComponents alloc] init];
		NSCalendar* Calendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSCalendarIdentifierGregorian];
		[DateComponents setDay: Day];
		[DateComponents setMonth: static_cast<int>(Month)];
		[DateComponents setYear: Year];

		NSDate* Date = [Calendar dateFromComponents: DateComponents];
		[Appboy sharedInstance].user.dateOfBirth = Date;

		[Calendar release];
		[DateComponents release];
	});

	return true;
}

bool UBrazeUserIOS::SetPushSubscriptionType(EBrazeNotificationSubscriptionType SubscriptionType)
{
	__block BOOL RetVal = NO;
	dispatch_sync(dispatch_get_main_queue(), ^{
		RetVal = [[Appboy sharedInstance].user setPushNotificationSubscriptionType: static_cast<ABKNotificationSubscriptionType>(SubscriptionType)];
	});

	return RetVal;
}

bool UBrazeUserIOS::SetEmailSubscriptionType(EBrazeNotificationSubscriptionType SubscriptionType)
{
	__block BOOL RetVal = NO;
	dispatch_sync(dispatch_get_main_queue(), ^{
		RetVal = [[Appboy sharedInstance].user setEmailNotificationSubscriptionType: static_cast<ABKNotificationSubscriptionType>(SubscriptionType)];
	});

	return RetVal;
}

bool UBrazeUserIOS::SetAttributionData(const FBrazeAttributionData& AttributionData)
{
	dispatch_sync(dispatch_get_main_queue(), ^{
		ABKAttributionData* NewAttributionData = [[ABKAttributionData alloc] initWithNetwork: BrazeConversions::FStringToNSString(AttributionData.Network)
		                                                                            campaign: BrazeConversions::FStringToNSString(AttributionData.Campaign)
		                                                                             adGroup: BrazeConversions::FStringToNSString(AttributionData.AdGroup)
		                                                                            creative: BrazeConversions::FStringToNSString(AttributionData.Creative)];
		[Appboy sharedInstance].user.attributionData = NewAttributionData;
		[NewAttributionData release];
	});

	return true;
}

void UBrazeUserIOS::SetLastKnownLocation(double Latitude, double Longitude, double Altitude, double Accuracy)
{
	dispatch_sync(dispatch_get_main_queue(), ^ {
		[[Appboy sharedInstance].user setLastKnownLocationWithLatitude: Latitude
		                                                     longitude: Longitude
		                                            horizontalAccuracy: Accuracy
													          altitude: Altitude
		                                              verticalAccuracy: Accuracy];								
	});
}

#endif 
