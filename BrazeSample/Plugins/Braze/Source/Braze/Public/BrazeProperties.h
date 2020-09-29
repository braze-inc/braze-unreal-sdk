// Copyright Braze Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BrazeProperties.generated.h"

UENUM(BlueprintType)
enum class EBrazeAnyType : uint8
{
	Invalid = 0,
	Int,
	Float,
	Boolean,
	String,
	Date
};

USTRUCT(BlueprintType)
struct FBrazeAny 
{	
	GENERATED_BODY()

	FBrazeAny() : DateValue(FDateTime::Now()) {}
	FBrazeAny(int32 Value) : Type(EBrazeAnyType::Int), IntValue(Value) {}
	FBrazeAny(float Value) : Type(EBrazeAnyType::Float), FloatValue(Value) {}
	FBrazeAny(bool Value) : Type(EBrazeAnyType::Boolean), BooleanValue(Value) {}
	FBrazeAny(const FString& Value) : Type(EBrazeAnyType::String), StringValue(Value) {}
	FBrazeAny(const FDateTime& Date) : Type(EBrazeAnyType::Date), DateValue(Date) {}

	/* Which value this instance represents */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBrazeAnyType Type = EBrazeAnyType::Invalid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 IntValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FloatValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool BooleanValue = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StringValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime DateValue;
};

USTRUCT(BlueprintType)
struct FBrazeProperties
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FBrazeAny> Properties;

	/**
	 * Add a value property
	 *
	 * @param Key String Key for property, must be <=255 characters, no leading dollar-sign
	 * @param Value a value which if a string, must be <=255 characters
	 */
	template <typename TValue>
	void Add(const FString& Key, TValue Value)
	{
		Properties.Add(Key, FBrazeAny(Value));
	}
};
