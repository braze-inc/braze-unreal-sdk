// Copyright Braze Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BrazeSampleFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BRAZESAMPLE_API UBrazeSampleFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	/**
	 * Example function for using the Custom Notification Delegate from outside the Braze Plugin
	 */
	UFUNCTION(BlueprintCallable)
	static void ConnectIOSNotificationDelegate();
};
