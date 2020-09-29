// Copyright Braze Inc. All Rights Reserved.

#pragma once

#include "Braze.h"
#include "CoreMinimal.h"
#include "BrazeIOS.generated.h"

class UBrazeConfig;
class UBrazeUser;
struct FBrazeProperties;

UCLASS()
class BRAZE_API UBrazeIOS : public UBraze
{
	GENERATED_BODY()

#if PLATFORM_IOS 

public:

	virtual bool Init(const UBrazeConfig& Config) final;

	virtual void ChangeUser(const FString& UserId) final;
	virtual void LogCustomEvent(const FString& EventName) final;
	virtual void LogCustomEventWithProperties(const FString& EventName, const FBrazeProperties& Properties) final;
	virtual void LogPurchase(const FString& ProductIdentifier, const FString& CurrencyCode, const FString& Price, const uint8 Quantity) final;
	virtual void LogPurchaseWithProperties(const FString& ProductIdentifier, const FString& CurrencyCode, const FString& Price, const uint8 Quantity, const FBrazeProperties& Properties) final;
	virtual void RequestImmediateDataFlush() final;

	virtual UBrazeUser* GetCurrentUser() const final;

private:

	void ApplicationRegisteredForRemoteNotifications(TArray<uint8> Token);
#endif
};
