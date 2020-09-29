// Copyright Braze Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BrazeProperties.h"
#include "Braze.generated.h"

class UBrazeConfig;
class UBrazeUser;

#undef PACKAGE_SCOPE
#ifdef BRAZE_PACKAGE
#define PACKAGE_SCOPE public
#else
#define PACKAGE_SCOPE private
#endif


UCLASS(BlueprintType, Abstract, ClassGroup=Braze)
class BRAZE_API UBraze : public UObject
{
	GENERATED_BODY()

public:

	/**
	* This method changes the user's ID.
	*
	* When you first start using Braze on a device, the user is considered "anonymous". You can use this method to
	* optionally identify a user with a unique ID, which enables the following:
	*
	*   - If the same user is identified on another device, their user profile, usage history and event history will
	*     be shared across devices.
	*
	*   - If your app is used by multiple people, you can assign each of them a unique identifier to track them
	*     separately. Only the most recent user on a particular device will receive push notifications and in-app
	*     messages.
	*
	*   - If you identify a user which has never been identified on another device, the entire history of that user as
	*     an "anonymous" user on this device will be preserved and associated with the newly identified user.
	*
	*   - However, if you identify a user which *has* been identified on another device, the previous anonymous
	*     history of the user on this device will not be added to the already existing profile for that user.
	*
	*   - Note that switching from one an anonymous user to an identified user or from one identified user to another is
	*     a relatively costly operation. When you request the
	*     user switch, the current session for the previous user is automatically closed and a new session is started.
	*     Braze will also automatically make a data refresh request to get the news feed, in-app message and other information
	*     for the new user.
	*
	*  Note: Once you identify a user, you cannot go back to the "anonymous" profile. The transition from anonymous
	*  to identified tracking only happens once because the initial anonymous user receives special treatment
	*  to allow for preservation of their history. We recommend against changing the user id just because your app
	*  has entered a "logged out" state because it separates this device from the user profile and thus you will be
	*  unable to target the previously logged out user with re-engagement campaigns. If you anticipate multiple
	*  users on the same device, but only want to target one of them when your app is in a logged out state, we recommend
	*  separately keeping track of the user ID you want to target while logged out and switching back to
	*  that user ID as part of your app's logout process.
	*
	* @param UserId The new user's ID (from the host application).
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ChangeUser(const FString& UserId) { }

	/**
	 * Adds an app specific event to event tracking log that's lazily pushed up to the server. Think of
	 *   events like counters. That is, each time you log an event, we'll update a counter for that user. Events should be
	 *   fairly broad like "beat level 1" or "watched video" instead of something more specific like "watched Katy
	 *   Perry's Last Friday Night" so you can create more broad user segments for targeting.
	 *
	 * @param EventName The name of the event to log.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void LogCustomEvent(const FString& EventName) { }
	
	/**
	 * Adds an app specific event to event tracking log that's lazily pushed up to the server. Think of
	 *   events like counters. That is, each time you log an event, we'll update a counter for that user. Events should be
	 *   fairly broad like "beat level 1" or "watched video" instead of something more specific like "watched Katy
	 *   Perry's Last Friday Night" so you can create more broad user segments for targeting.
	 *
	 * @param EventName The name of the event to log.
	 * @param Properties Properties to associate with this custom event
	 */ 
	UFUNCTION(BlueprintCallable)
	virtual void LogCustomEventWithProperties(const FString& EventName, const FBrazeProperties& Properties) { }

	/**
	 * Logs a purchase made in the application.
	 * @param ProductIdentifier A String indicating the product that was purchased. Usually the product identifier in the
	 * iTunes store.
	 * @param CurrencyCode Currencies should be represented as an ISO 4217 currency code.
	 * Supported currency symbols include: AED, AFN, ALL, AMD, ANG, AOA, ARS, AUD, AWG, AZN, BAM, BBD, BDT, BGN, BHD, BIF,
	 * BMD, BND, BOB, BRL, BSD, BTC, BTN, BWP, BYR, BZD, CAD, CDF, CHF, CLF, CLP, CNY, COP, CRC, CUC, CUP, CVE, CZK, DJF,
	 * DKK, DOP, DZD, EEK, EGP, ERN, ETB, EUR, FJD, FKP, GBP, GEL, GGP, GHS, GIP, GMD, GNF, GTQ, GYD, HKD, HNL, HRK, HTG, HUF,
	 * IDR, ILS, IMP, INR, IQD, IRR, ISK, JEP, JMD, JOD, JPY, KES, KGS, KHR, KMF, KPW, KRW, KWD, KYD, KZT, LAK, LBP, LKR, LRD,
	 * LSL, LTL, LVL, LYD, MAD, MDL, MGA, MKD, MMK, MNT, MOP, MRO, MTL, MUR, MVR, MWK, MXN, MYR, MZN, NAD, NGN, NIO, NOK, NPR,
	 * NZD, OMR, PAB, PEN, PGK, PHP, PKR, PLN, PYG, QAR, RON, RSD, RUB, RWF, SAR, SBD, SCR, SDG, SEK, SGD, SHP, SLL, SOS, SRD,
	 * STD, SVC, SYP, SZL, THB, TJS, TMT, TND, TOP, TRY, TTD, TWD, TZS, UAH, UGX, USD, UYU, UZS, VEF, VND, VUV, WST, XAF, XAG,
	 * XAU, XCD, XDR, XOF, XPD, XPF, XPT, YER, ZAR, ZMK, ZMW and ZWL. Any other provided currency symbol will result in a logged
	 * warning and no other action taken by the SDK.
	 * @param Price As an example, USD should be reported as Dollars.Cents, whereas JPY should
	 * be reported as a whole number of Yen. 
	 * @param Quantity An unsigned number to indicate the purchase quantity. This number must be greater than 0 but no larger than 100.
	 *
	 * Note: Braze supports purchases in multiple currencies. Purchases that you report in a currency other than USD will
	 * be shown in the dashboard in USD based on the exchange rate at the date they were reported.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void LogPurchase(const FString& ProductIdentifier, const FString& CurrencyCode, const FString& Price, const uint8 Quantity) { }

	/**
	 * Logs a purchase made in the application.
	 * @param ProductIdentifier A String indicating the product that was purchased. Usually the product identifier in the
	 * iTunes store.
	 * @param CurrencyCode Currencies should be represented as an ISO 4217 currency code.
	 * Supported currency symbols include: AED, AFN, ALL, AMD, ANG, AOA, ARS, AUD, AWG, AZN, BAM, BBD, BDT, BGN, BHD, BIF,
	 * BMD, BND, BOB, BRL, BSD, BTC, BTN, BWP, BYR, BZD, CAD, CDF, CHF, CLF, CLP, CNY, COP, CRC, CUC, CUP, CVE, CZK, DJF,
	 * DKK, DOP, DZD, EEK, EGP, ERN, ETB, EUR, FJD, FKP, GBP, GEL, GGP, GHS, GIP, GMD, GNF, GTQ, GYD, HKD, HNL, HRK, HTG, HUF,
	 * IDR, ILS, IMP, INR, IQD, IRR, ISK, JEP, JMD, JOD, JPY, KES, KGS, KHR, KMF, KPW, KRW, KWD, KYD, KZT, LAK, LBP, LKR, LRD,
	 * LSL, LTL, LVL, LYD, MAD, MDL, MGA, MKD, MMK, MNT, MOP, MRO, MTL, MUR, MVR, MWK, MXN, MYR, MZN, NAD, NGN, NIO, NOK, NPR,
	 * NZD, OMR, PAB, PEN, PGK, PHP, PKR, PLN, PYG, QAR, RON, RSD, RUB, RWF, SAR, SBD, SCR, SDG, SEK, SGD, SHP, SLL, SOS, SRD,
	 * STD, SVC, SYP, SZL, THB, TJS, TMT, TND, TOP, TRY, TTD, TWD, TZS, UAH, UGX, USD, UYU, UZS, VEF, VND, VUV, WST, XAF, XAG,
	 * XAU, XCD, XDR, XOF, XPD, XPF, XPT, YER, ZAR, ZMK, ZMW and ZWL. Any other provided currency symbol will result in a logged
	 * warning and no other action taken by the SDK.
	 * @param Price As an example, USD should be reported as Dollars.Cents, whereas JPY should
	 * be reported as a whole number of Yen.
	 * @param Quantity An unsigned number to indicate the purchase quantity. This number must be greater than 0 but no larger than 100.
	 * @param Properties Properties to associate with this purchase.
	 *
	 * Note: Braze supports purchases in multiple currencies. Purchases that you report in a currency other than USD will
	 * be shown in the dashboard in USD based on the exchange rate at the date they were reported.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void LogPurchaseWithProperties(const FString& ProductIdentifier, const FString& CurrencyCode, const FString& Price, const uint8 Quantity, const FBrazeProperties& Properties) { }

	/**
	 * Requests an immediate flush of any analytics data waiting to be sent to Braze's servers.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void RequestImmediateDataFlush() { }

	/**
	 * Get a UObject representing the current user
	 *
	 * @returns UBrazeUser
	 */
	UFUNCTION(BlueprintCallable)
	virtual UBrazeUser* GetCurrentUser() const { return nullptr; }

PACKAGE_SCOPE:
	/**
	 * Initialize Braze with the passed Config
	 * NOTE: This function is called by UBrazeSubsystem, and should NOT be called manually
	 *
	 * @param Config
	 */
	virtual bool Init(const UBrazeConfig& Config) { return false; }
};
