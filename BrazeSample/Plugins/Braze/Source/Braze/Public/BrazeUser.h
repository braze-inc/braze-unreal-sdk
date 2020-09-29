// Copyright Braze Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BrazeAttributionData.h"

#include "BrazeUser.generated.h"

UENUM(BlueprintType)
enum class EBrazeGender : uint8 
{
	Male = 0, 
	Female,
	Other,
	NotApplicable,
	PreferNotToSay,
	Unknown
};

UENUM(BlueprintType)
enum class EBrazeMonth : uint8
{
	January = 0,
	February,
	March, 
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};

UENUM(BlueprintType)
enum class EBrazeNotificationSubscriptionType : uint8
{
	OptedIn = 0,
	Subscribed,
	Unsubscribed,
};

UCLASS(BlueprintType, Abstract, ClassGroup=Braze)
class BRAZE_API UBrazeUser : public UObject
{
	GENERATED_BODY()
	
public:

	/**
	 * Adds an an alias for the current user.  Individual (alias, label) pairs can exist on one and only one user.
	 * If a different user already has this alias or external user id, the alias attempt will be rejected
	 * on the server.
	 *
	 * @param Alias The alias of the current user.
	 * @param Label The label of the alias; used to differentiate it from other aliases for the user.
	 * @return Whether or not the alias and label are valid. Does not guarantee they won't collide with
	 *         an existing pair.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool AddAlias(const FString& Alias, const FString& Label) { return false; }

	/**
	 * @param AttributeKey The String name of the custom user attribute
	 * @param Value A String value to set as a custom attribute
	 * @return whether or not the custom user attribute was set successfully; If not, your key might have been nil or empty,
	 *         your value might have been invalid (either nil, or not of the correct type), or you tried to set a value for
	 *         one of the reserved keys. Please check the log for more details about the specific failure you encountered.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetCustomUserAttributeString(const FString& AttributeKey, const FString& Value) { return false; }

	/**
	 * @param AttributeKey The String name of the custom user attribute
	 * @param Value An integer value to set as a custom attribute
	 * @return whether or not the custom user attribute was set successfully; If not, your key might have been nil or empty,
	 *         your value might have been invalid (either nil, or not of the correct type), or you tried to set a value for
	 *         one of the reserved keys. Please check the log for more details about the specific failure you encountered.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetCustomUserAttributeInt(const FString& AttributeKey, int32 Value) { return false; }

	/**
	 * @param AttributeKey The String name of the custom user attribute
	 * @param Value A long value to set as a custom attribute
	 * @return whether or not the custom user attribute was set successfully; If not, your key might have been nil or empty,
	 *         your value might have been invalid (either nil, or not of the correct type), or you tried to set a value for
	 *         one of the reserved keys. Please check the log for more details about the specific failure you encountered.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetCustomUserAttributeLong(const FString& AttributeKey, int64 Value) { return false; }
	
	/**
	 * @param AttributeKey The String name of the custom user attribute
	 * @param Value A float value to set as a custom attribute
	 * @return whether or not the custom user attribute was set successfully; If not, your key might have been nil or empty,
	 *         your value might have been invalid (either nil, or not of the correct type), or you tried to set a value for
	 *         one of the reserved keys. Please check the log for more details about the specific failure you encountered.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetCustomUserAttributeFloat(const FString& AttributeKey, float Value) { return false; }

	/**
	 * @param AttributeKey The String name of the custom user attribute
	 * @param Value A double value to set as a custom attribute
	 * @return whether or not the custom user attribute was set successfully; If not, your key might have been nil or empty,
	 *         your value might have been invalid (either nil, or not of the correct type), or you tried to set a value for
	 *         one of the reserved keys. Please check the log for more details about the specific failure you encountered.
	 * NOTE: UFUNCTION doesn't support double as a param type
	 */
	virtual bool SetCustomUserAttributeDouble(const FString& AttributeKey, double Value) { return false; }

	/**
	 * @param AttributeKey The String name of the custom user attribute
	 * @param Value A boolean value to set as a custom attribute
	 * @return whether or not the custom user attribute was set successfully; If not, your key might have been nil or empty,
	 *         your value might have been invalid (either nil, or not of the correct type), or you tried to set a value for
	 *         one of the reserved keys. Please check the log for more details about the specific failure you encountered.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetCustomUserAttributeBool(const FString& AttributeKey, bool Value) { return false; }

	/**
	 * @param AttributeKey The String name of the custom user attribute
	 * @param Value A Date value to set as a custom attribute
	 * @return whether or not the custom user attribute was set successfully; If not, your key might have been nil or empty,
	 *         your value might have been invalid (either nil, or not of the correct type), or you tried to set a value for
	 *         one of the reserved keys. Please check the log for more details about the specific failure you encountered.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetCustomUserAttributeDate(const FString& AttributeKey, const FDateTime& Date) { return false; }

	/**
	 * Sets a string array from a custom attribute specified by the key.
	 *
	 * @param AttributeKey The custom attribute key
	 * @param Values A string array to set as a custom attribute. If this value is nil, then Braze will unset the custom
	 *        attribute and remove the corresponding array if there is one.
	 * @return true if the operation was successful
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetCustomAttributeArray(const FString& AttributeKey, const TArray<FString>& Values) { return false; }

	/**
	 * @param AttributeKey The String name of the custom user attribute to unset
	 * @return whether or not the custom user attribute was unset successfully
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool UnsetCustomAttribute(const FString& AttributeKey) { return false; }

	/**
	 * Increments the value of an custom attribute by a given amount. Only integer and long custom attributes can be
	 * incremented. Attempting to increment a custom attribute that is not an integer or a long will be ignored. If
	 * you increment a custom attribute that has not previously been set, a custom attribute will be created and assigned
	 * the value of incrementValue. To decrement the value of a custom attribute, use a negative incrementValue.
	 *
	 * @param AttributeKey The identifier of the custom attribute
	 * @param IncrementValue The amount by which to increment the custom attribute
	 * @return true if the increment for the custom attribute of given key is saved
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool IncrementCustomUserAttribute(const FString& AttributeKey, int32 IncrementValue = 1) { return false; }

	/**
	 * Adds the string value to a custom attribute string array specified by the key. If you add a key that has not
	 * previously been set, a custom attribute string array will be created containing the value.
	 *
	 * @param AttributeKey The custom attribute key
	 * @param Value A string to be added to the custom attribute string array
	 * @return true if the operation was successful
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool AddToCustomAttributeArray(const FString& AttributeKey, const FString& Value) { return false; }

	/**
	 * Removes the string value from a custom attribute string array specified by the key. If you remove a key that has not
	 * previously been set, nothing will be changed.
	 *
	 * @param AttributeKey The custom attribute key
	 * @param Value A string to be removed from the custom attribute string array
	 * @return true if the operation was successful
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool RemoveFromCustomAttributeArray(const FString& AttributeKey, const FString& Value) { return false; }

	/**
	 * Set the User's Email
	 *
	 * @param Email The email address
	 * @return true if the field was set successfully. Check the logs for more info.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetEmail(const FString& Email) { return false; }

	/**
	 * Set the User's First Name
	 *
	 * @param FirstName The first name
	 * @return true if the field was set successfully. Check the logs for more info.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetFirstName(const FString& FirstName) { return false; }

	/**
	 * Set the User's Last Name
	 * 
	 * @param LastName The last name
	 * @return true if the field was set successfully. Check the logs for more info.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetLastName(const FString& LastName) { return false; }

	/**
	 * Set the User's Gender
	 *
	 * @param Gender The gender
	 * @return true if the field was set successfully. Check the logs for more info.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetGender(EBrazeGender Gender) { return false; }

	/**
	 * Set the User's Language
	 *
	 * @param Language The language
	 * @return true if the field was set successfully. Check the logs for more info.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetLanguage(const FString& Language) { return false; }

	/**
	 * Set the User's Country
	 *
	 * @param Country The country
	 * @return true if the field was set successfully. Check the logs for more info.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetCountry(const FString& Country) { return false; }

	/**
	 * Set the User's Home City
	 *
	 * @param HomeCity The home city
	 * @return true if the field was set successfully. Check the logs for more info.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetHomeCity(const FString& HomeCity) { return false; }

	/**
	 * Set the User's Phone number
	 *
	 * @param PhoneNumber The phone number
	 * @return true if the field was set successfully. Check the logs for more info.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetPhoneNumber(const FString& PhoneNumber) { return false; }

	/**
	 * Set the User's Birthday
	 *
	 * @param Year The year
	 * @param Month The month 
	 * @param Day The day
	 * @return true if the field was set successfully. Check the logs for more info.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetDateOfBirth(int32 Year, EBrazeMonth Month, int32 Day) { return false; }

	/**
	 * Sets the push notification subscription status of the user.
	 *
	 * @param SubscriptionType The push notification subscription type
	 * @return true if the field was set successfully. Check the logs for more info.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetPushSubscriptionType(EBrazeNotificationSubscriptionType SubscriptionType) { return false; }
	 
	/**
	 * Sets the email notification subscription status of the user.
	 *
	 * @param SubscriptionType The email notification subscription type
	 * @return true if the field was set successfully. Check the logs for more info.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetEmailSubscriptionType(EBrazeNotificationSubscriptionType SubscriptionType) { return false; }

	/**
	 * Sets the attribution information for the user. For in apps that have an install tracking integration.
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool SetAttributionData(const FBrazeAttributionData& AttributionData) { return false; }

	/**
	* Sets the last known location for the user. Intended for use with ABKDisableLocationAutomaticTrackingOptionKey set to YES
	* when starting Braze, so that the only locations being set are by the integrating app.  Otherwise, calls to this
	* method will be contending with automatic location update events.
	*
	* @param Latitude The latitude of the User's location in degrees, the number should be in the range of [-90, 90]
	* @param Longitude The longitude of the User's location in degrees, the number should be in the range of [-180, 180]
	* @param Altitude The altitude of the User's location in meters
	* @param Accuracy The accuracy of the User's location in meters, the number should not be negative
	*/
	UFUNCTION(BlueprintCallable)
	virtual void SetLastKnownLocation(float Latitude, float Longitude, float Altitude, float Accuracy) { SetLastKnownLocation(static_cast<double>(Latitude), static_cast<double>(Longitude), static_cast<double>(Altitude), static_cast<double>(Accuracy)); }
	
	/**
	* Sets the last known location for the user. Intended for use with ABKDisableLocationAutomaticTrackingOptionKey set to YES
	* when starting Braze, so that the only locations being set are by the integrating app.  Otherwise, calls to this
	* method will be contending with automatic location update events.
	*
	* @param Latitude The latitude of the User's location in degrees, the number should be in the range of [-90, 90]
	* @param Longitude The longitude of the User's location in degrees, the number should be in the range of [-180, 180]
	* @param Altitude The altitude of the User's location in meters
	* @param Accuracy The accuracy of the User's location in meters, the number should not be negative
	*/
	virtual void SetLastKnownLocation(double Latitude, double Longitude, double Altitude, double Accuracy) { ; }
};
