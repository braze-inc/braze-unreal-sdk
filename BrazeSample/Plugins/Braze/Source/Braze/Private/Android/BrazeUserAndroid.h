// Copyright Braze Inc. All Rights Reserved.

#pragma once

#include "BrazeUser.h"
#include "CoreMinimal.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#endif

#include "BrazeUserAndroid.generated.h"

UCLASS()
class BRAZE_API UBrazeUserAndroid : public UBrazeUser
{
	GENERATED_BODY()

#if PLATFORM_ANDROID 

public:
	void Initialize(const jobject& BrazeInstance);
	virtual void BeginDestroy() final;

	virtual bool AddAlias(const FString& Alias, const FString& Label) final;

	virtual bool SetCustomUserAttributeString(const FString& AttributeKey, const FString& Value) final;
	virtual bool SetCustomUserAttributeInt(const FString& AttributeKey, int32 Value) final;
	virtual bool SetCustomUserAttributeLong(const FString& AttributeKey, int64 Value) final;
	virtual bool SetCustomUserAttributeFloat(const FString& AttributeKey, float Value) final;
	virtual bool SetCustomUserAttributeDouble(const FString& AttributeKey, double Value) final;
	virtual bool SetCustomUserAttributeBool(const FString& AttributeKey, bool Value) final;
	virtual bool SetCustomUserAttributeDate(const FString& AttributeKey, const FDateTime& Date) final;
	virtual bool SetCustomAttributeArray(const FString& AttributeKey, const TArray<FString>& Values) final;
	virtual bool UnsetCustomAttribute(const FString& AttributeKey) final;
	virtual bool IncrementCustomUserAttribute(const FString& AttributeKey, int32 IncrementValue = 1) final;
	virtual bool AddToCustomAttributeArray(const FString& AttributeKey, const FString& Value) final;
	virtual bool RemoveFromCustomAttributeArray(const FString& AttributeKey, const FString& Value) final;

	virtual bool SetEmail(const FString& Email) final;
	virtual bool SetFirstName(const FString& FirstName) final;
	virtual bool SetLastName(const FString& LastName) final;
	virtual bool SetGender(EBrazeGender Gender) final;
	virtual bool SetLanguage(const FString& Language) final;
	virtual bool SetCountry(const FString& Country) final;
	virtual bool SetHomeCity(const FString& HomeCity) final;
	virtual bool SetPhoneNumber(const FString& PhoneNumber) final;
	virtual bool SetDateOfBirth(int32 Year, EBrazeMonth Month, int32 Day) final;
	virtual bool SetPushSubscriptionType(EBrazeNotificationSubscriptionType SubscriptionType) final;
	virtual bool SetEmailSubscriptionType(EBrazeNotificationSubscriptionType SubscriptionType) final;
	virtual bool SetAttributionData(const FBrazeAttributionData& AttributionData) final;

	virtual void SetLastKnownLocation(double Latitude, double Longitude, double Altitude, double Accuracy) final;

protected:
	
	jobject UserJObject = nullptr;

#endif
};
