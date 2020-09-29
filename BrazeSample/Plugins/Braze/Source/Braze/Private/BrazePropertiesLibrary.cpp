// Copyright Braze Inc. All Rights Reserved.

#include "BrazePropertiesLibrary.h"
#include "BrazeModule.h"
#include "BrazeProperties.h"

void UBrazePropertiesLibrary::AddInt(UPARAM(ref) FBrazeProperties& Properties, const FString& Key, int32 Value)
{
	Properties.Add(Key, Value);
}

void UBrazePropertiesLibrary::AddFloat(UPARAM(ref) FBrazeProperties& Properties, const FString& Key, float Value)
{
	Properties.Add(Key, Value);
}

void UBrazePropertiesLibrary::AddBoolean(UPARAM(ref) FBrazeProperties& Properties, const FString& Key, bool Value)
{
	Properties.Add(Key, Value);
}

void UBrazePropertiesLibrary::AddString(UPARAM(ref) FBrazeProperties& Properties, const FString& Key, const FString& Value)
{
	Properties.Add(Key, Value);
}

void UBrazePropertiesLibrary::AddDate(UPARAM(ref) FBrazeProperties& Properties, const FString& Key, const FDateTime& Value)
{
	Properties.Add(Key, Value);
}

FBrazeAny UBrazePropertiesLibrary::MakeBrazeAnyInt(int32 Value)
{
	return FBrazeAny(Value);
}

FBrazeAny UBrazePropertiesLibrary::MakeBrazeAnyFloat(float Value)
{
	return FBrazeAny(Value);
}

FBrazeAny UBrazePropertiesLibrary::MakeBrazeAnyBoolean(bool Value)
{
	return FBrazeAny(Value);
}

FBrazeAny UBrazePropertiesLibrary::MakeBrazeAnyString(const FString& Value)
{
	return FBrazeAny(Value);
}

FBrazeAny UBrazePropertiesLibrary::MakeBrazeAnyDate(const FDateTime& Value)
{
	return FBrazeAny(Value);
}
