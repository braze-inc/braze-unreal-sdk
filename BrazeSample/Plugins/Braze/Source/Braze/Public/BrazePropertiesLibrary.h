// Copyright Braze Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BrazeProperties.h"
#include "BrazePropertiesLibrary.generated.h"

UCLASS()
class BRAZE_API UBrazePropertiesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Add an integer property
	 *
	 * @param Properties Property struct to modify
	 * @param Key String Key for property, must be <=255 characters, no leading dollar-sign
	 * @param Value integer value
	 */
	UFUNCTION(BlueprintCallable)
	static void AddInt(UPARAM(ref) FBrazeProperties& Properties, const FString& Key, int32 Value);

	/**
	 * Add a float property
	 *
	 * @param Properties Property struct to modify
	 * @param Key String Key for property, must be <=255 characters, no leading dollar-sign
	 * @param Value float value
	 */
	UFUNCTION(BlueprintCallable)
	static void AddFloat(UPARAM(ref) FBrazeProperties& Properties, const FString& Key, float Value);

	/**
	 * Add a bool property
	 *
	 * @param Properties Property struct to modify
	 * @param Key String Key for property, must be <=255 characters, no leading dollar-sign
	 * @param Value bool value
	 */
	UFUNCTION(BlueprintCallable)
	static void AddBoolean(UPARAM(ref) FBrazeProperties& Properties, const FString& Key, bool Value);

	/**
	 * Add a String property
	 *
	 * @param Properties Property struct to modify
	 * @param Key String Key for property, must be <=255 characters, no leading dollar-sign
	 * @param Value String value, must be <=255 characters
	 */
	UFUNCTION(BlueprintCallable)
	static void AddString(UPARAM(ref) FBrazeProperties& Properties, const FString& Key, const FString& Value);

	/**
	 * Add a Date property
	 *
	 * @param Properties Property struct to modify
	 * @param Key String Key for property, must be <=255 characters, no leading dollar-sign
	 * @param Value Date value
	 */
	UFUNCTION(BlueprintCallable)
	static void AddDate(UPARAM(ref) FBrazeProperties& Properties, const FString& Key, const FDateTime& Value);

	/**
	 * Helper function to create an FBrazeAny Int value
	 * 
	 * @param Value int value
	 */
	UFUNCTION(BlueprintPure)
	static FBrazeAny MakeBrazeAnyInt(int32 Value);

	/**
	 * Helper function to create an FBrazeAny Float value
	 *
	 * @param Value float value
	 */
	UFUNCTION(BlueprintPure)
	static FBrazeAny MakeBrazeAnyFloat(float Value);

	/**
	 * Helper function to create an FBrazeAny Boolean value
	 *
	 * @param Value bool value
	 */
	UFUNCTION(BlueprintPure)
	static FBrazeAny MakeBrazeAnyBoolean(bool Value);

	/**
	 * Helper function to create an FBrazeAny String value
	 *
	 * @param Value FString value
	 */
	UFUNCTION(BlueprintPure)
	static FBrazeAny MakeBrazeAnyString(const FString& Value);

	/**
	 * Helper function to create an FBrazeAny DateTime value
	 *
	 * @param Value FDateTime value
	 */
	UFUNCTION(BlueprintPure)
	static FBrazeAny MakeBrazeAnyDate(const FDateTime& Value);
};
