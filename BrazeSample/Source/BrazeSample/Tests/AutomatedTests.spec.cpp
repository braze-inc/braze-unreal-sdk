// Copyright Braze Inc. All Rights Reserved.

#include "Braze.h"
#include "BrazeAttributionData.h"
#include "BrazeSubsystem.h"
#include "BrazeUser.h"
#include "Misc/AutomationTest.h"

BEGIN_DEFINE_SPEC(FBrazeSpec, "Braze.Unit", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
	TWeakObjectPtr<UBraze> Braze;
END_DEFINE_SPEC(FBrazeSpec)

void FBrazeSpec::Define()
{
	Describe("Analytics", [this]() {
		BeforeEach([this]() {
			if (!Braze.IsValid())
			{
				UBrazeSubsystem* const BrazeSubsystem = GEngine->GetEngineSubsystem<UBrazeSubsystem>();
				if (!TestTrue("IsValid(BrazeSubsystem)", IsValid(BrazeSubsystem)))
				{
					return;
				}

				Braze = BrazeSubsystem->InitializeBraze();
				if (!TestTrue("Braze.IsValid()", Braze.IsValid()))
				{
					return;
				}

				// Ensure each test uses AutomatedTest as a name to confirm details on the dashboard.
				Braze->ChangeUser(TEXT("AutomatedTest"));
			}
		});

		It("should submit a logCustomEvent of \"AutomatedTestEvent\" with the property \"TestProperty\" set to 1", [this]() {
			if (!Braze.IsValid())
			{
				return;
			}

			FBrazeProperties Properties;
			Properties.Add<FString>(TEXT("TestString"), TEXT("Test"));
			Properties.Add<int32>(TEXT("TestInt"), 5);
			Properties.Add<float>(TEXT("TestFloat"), 1.5f);
			Properties.Add<bool>(TEXT("TestBool"), true);
			Properties.Add<FDateTime>(TEXT("TestDate"), FDateTime::Now());

			Braze->LogCustomEventWithProperties(TEXT("AutomatedTestEvent"), Properties);
		});

		It("should set a custom user attribute of \"AutomatedTestAttribute\" with the value 1", [this]() {
			if (!Braze.IsValid())
			{
				return;
			}

			UBrazeUser* const BrazeUser = Braze->GetCurrentUser();
			if (!TestTrue("IsValid(BrazeUser)", IsValid(BrazeUser)))
			{
				return;
			}

			TestTrue("BrazeUser->SetCustomUserAttributeInt", BrazeUser->SetCustomUserAttributeInt(TEXT("AutomatedTestAttribute"), 1));
		});

		It("should increment custom user attribute of \"AutomatedTestAttribute\" by 9", [this]() {
			if (!Braze.IsValid())
			{
				return;
			}

			UBrazeUser* const BrazeUser = Braze->GetCurrentUser();
			if (!TestTrue("IsValid(BrazeUser)", IsValid(BrazeUser)))
			{
				return;
			}

			TestTrue("BrazeUser->IncrementCustomUserAttribute", BrazeUser->IncrementCustomUserAttribute(TEXT("AutomatedTestAttribute"), 9));
		});

		It("should add a custom attribute string array named \"AutomatedTestArray\" with the values \"Test1\" and \"Test2\"", [this]() {
			if (!Braze.IsValid())
			{
				return;
			}

			UBrazeUser* const BrazeUser = Braze->GetCurrentUser();
			if (!TestTrue("IsValid(BrazeUser)", IsValid(BrazeUser)))
			{
				return;
			}

			 TestTrue("BrazeUser->SetCustomAttributeArray", BrazeUser->SetCustomAttributeArray(TEXT("AutomatedTestArray"), TArray<FString> { TEXT("Test1"), TEXT("Test2")}));
		});

		It("should add the string \"TestAdd\" to the \"AutomatedTestArray\" custom attribute", [this] {
			if (!Braze.IsValid())
			{
				return;
			}

			UBrazeUser* const BrazeUser = Braze->GetCurrentUser();
			if (!TestTrue("IsValid(BrazeUser)", IsValid(BrazeUser)))
			{
				return;
			}

			TestTrue("BrazeUser->AddToCustomAttributeArray", BrazeUser->AddToCustomAttributeArray(TEXT("AutomatedTestArray"), TEXT("TestAdd")));
		});

		It("should remove the string \"Test1\" from the \"AutomatedTestArray\" custom attribute", [this] {
			if (!Braze.IsValid())
			{
				return;
			}

			UBrazeUser* const BrazeUser = Braze->GetCurrentUser();
			if (!TestTrue("IsValid(BrazeUser)", IsValid(BrazeUser)))
			{
				return;
			}

			TestTrue("BrazeUser->RemoveFromCustomAttributeArray", BrazeUser->RemoveFromCustomAttributeArray(TEXT("AutomatedTestArray"), TEXT("Test1")));
		});

		It("should set each profile attribute: email, first/last name, gender, language, country, home city, phone number, DOB, notification types, and attribution data", [this]() {
			if (!Braze.IsValid())
			{
				return;
			}

			UBrazeUser* const BrazeUser = Braze->GetCurrentUser();
			if (!TestTrue("IsValid(BrazeUser)", IsValid(BrazeUser)))
			{
				return;
			}

			TestTrue("BrazeUser->SetEmail", BrazeUser->SetEmail(TEXT("Automated@Test.com")));
			TestTrue("BrazeUser->SetFirstName", BrazeUser->SetFirstName(TEXT("Automated")));
			TestTrue("BrazeUser->SetLastName", BrazeUser->SetLastName(TEXT("TEST")));
			TestTrue("BrazeUser->SetGender", BrazeUser->SetGender(EBrazeGender::Other));
			TestTrue("BrazeUser->SetLanguage", BrazeUser->SetLanguage(TEXT("en_US")));
			TestTrue("BrazeUser->SetCountry", BrazeUser->SetCountry(TEXT("US")));
			TestTrue("BrazeUser->SetHomeCity", BrazeUser->SetHomeCity(TEXT("New York, NY")));
			TestTrue("BrazeUser->SetPhoneNumber", BrazeUser->SetPhoneNumber(TEXT("555-555-4444")));
			TestTrue("BrazeUser->SetDateOfBirth", BrazeUser->SetDateOfBirth(1990, EBrazeMonth::February, 5));
			TestTrue("BrazeUser->SetPushSubscriptionType", BrazeUser->SetPushSubscriptionType(EBrazeNotificationSubscriptionType::OptedIn));
			TestTrue("BrazeUser->SetEmailSubscriptionType", BrazeUser->SetEmailSubscriptionType(EBrazeNotificationSubscriptionType::OptedIn));
			TestTrue("BrazeUser->SetAttributionData", BrazeUser->SetAttributionData(FBrazeAttributionData(TEXT("TestNetwork"), TEXT("TestCampaign"), TEXT("TestAdGroup"), TEXT("TestCreative"))));
		});

		It("should set the last known location", [this]() {
			if (!Braze.IsValid())
			{
				return;
			}

			UBrazeUser* const BrazeUser = Braze->GetCurrentUser();
			if (!TestTrue("IsValid(BrazeUser)", IsValid(BrazeUser)))
			{
				return;
			}

			BrazeUser->SetLastKnownLocation(40.688999, -74.074104, 300.0, 50.0);
		});

		It("should log purchase \"AutomatedTestPurchase\" with properties set to \"TestProperty\"=1", [this]() {
			if (!Braze.IsValid())
			{
				return;
			}

			FBrazeProperties Properties;
			Properties.Add(TEXT("TestProperty"), 1);
			Braze->LogPurchaseWithProperties(TEXT("AutomatedTestPurchase"), TEXT("USD"), TEXT("1.99"), 1, Properties);
		});

		It("should request an immediate data flush", [this]() {
			if (!Braze.IsValid())
			{
				return;
			}
			
			Braze->RequestImmediateDataFlush();
		});
	});
}
