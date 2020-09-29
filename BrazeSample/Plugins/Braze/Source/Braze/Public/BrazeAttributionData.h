// Copyright Braze Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BrazeAttributionData.generated.h"

USTRUCT(BlueprintType)
struct BRAZE_API FBrazeAttributionData
{
	GENERATED_BODY()

	FBrazeAttributionData() = default;
	FBrazeAttributionData(const FString& InNetwork, const FString& InCampaign, const FString& InAdGroup, const FString& InCreative) 
	 : Network(InNetwork), Campaign(InCampaign), AdGroup(InAdGroup), Creative(InCreative)
	{ }

	/**
	 * The attribution network
	 */
	UPROPERTY(BlueprintReadWrite)
	FString Network;

	/**
	 * The attribution campaign
	 */
	UPROPERTY(BlueprintReadWrite)
	FString Campaign;

	/**
	 * The attribution adgroup
	 */
	UPROPERTY(BlueprintReadWrite)
	FString AdGroup;

	/**
	 * The attribution creative
	 */
	UPROPERTY(BlueprintReadWrite)
	FString Creative;
};
