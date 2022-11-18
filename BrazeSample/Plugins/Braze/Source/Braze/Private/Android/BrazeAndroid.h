// Copyright Braze Inc. All Rights Reserved.

#pragma once

#include "Braze.h"
#include "CoreMinimal.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#endif

#include "BrazeAndroid.generated.h"

class UBrazeConfig;
class UBrazeUser;
struct FBrazeProperties;

UCLASS()
class BRAZE_API UBrazeAndroid : public UBraze
{
	GENERATED_BODY()

#if PLATFORM_ANDROID 

public:
	virtual void BeginDestroy() final;

	virtual bool Init(const UBrazeConfig& Config) final;
	
	virtual void ChangeUser(const FString& UserId) final;
	virtual void LogCustomEvent(const FString& EventName) final;
	virtual void LogCustomEventWithProperties(const FString& EventName, const FBrazeProperties& Properties) final;
	virtual void LogPurchase(const FString& ProductIdentifier, const FString& CurrencyCode, const FString& Price, const uint8 Quantity) final;
	virtual void LogPurchaseWithProperties(const FString& ProductIdentifier, const FString& CurrencyCode, const FString& Price, const uint8 Quantity, const FBrazeProperties& Properties) final;
	virtual void RequestImmediateDataFlush() final;

	virtual UBrazeUser* GetCurrentUser() const final;

	FScopedJavaObject<jobject> GetBrazeInstance() const;

protected:
	jobject ApplicationContext;

#endif
};
