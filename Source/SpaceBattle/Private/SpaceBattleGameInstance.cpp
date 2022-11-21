// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceBattleGameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "../Enums/EAsyncOperationOutExec.h"


USpaceBattleGameInstance::USpaceBattleGameInstance() {


}

void USpaceBattleGameInstance::Init()
{
	Super::Init();

	OnlineSubsystem = IOnlineSubsystem::Get();

}

void USpaceBattleGameInstance::Login(TEnumAsByte<EAsyncOperationOutExec>& Outcome)
{
	Outcome = EAsyncOperationOutExec::Failed;
	if (OnlineSubsystem) 
	{
		if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface()) 
		{
			FOnlineAccountCredentials Credentials;

			Credentials.Id = FString();
			Credentials.Token = FString();
			Credentials.Type = FString("accountportal");

			Identity->OnLoginCompleteDelegates->AddUObject(this, &USpaceBattleGameInstance::OnLoginComplete);

			// TODO
			// Outcome = EOutcomePins::Success;


			Identity->Login(0, Credentials);
		}
	}
}
void USpaceBattleGameInstance::OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	UE_LOG(LogTemp, Warning, TEXT("Logged in: %d"), bWasSuccessful);

	if (OnlineSubsystem)
	{
		if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			Identity->ClearOnLoginCompleteDelegates(0, this);
		}
	}
}


void USpaceBattleGameInstance::CreateSession()
{
	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			FOnlineSessionSettings SessionSettings;
			SessionSettings.bIsDedicated = false;
			SessionSettings.bIsDedicated = true;
			SessionSettings.bIsLANMatch = true;
			SessionSettings.NumPublicConnections = 5;
			SessionSettings.bAllowJoinInProgress = true;
			SessionSettings.bAllowJoinViaPresence = true;
			SessionSettings.bUsesPresence = true;
			SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &USpaceBattleGameInstance::OnCreateSessionComplete);
			SessionPtr->CreateSession(0, FName("Test Session"), SessionSettings);
		}
	}
}

void USpaceBattleGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Success: %d"), bWasSuccessful);


	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->ClearOnCreateSessionCompleteDelegates(this);
		}
	}
}
