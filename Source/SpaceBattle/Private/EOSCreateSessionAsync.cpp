// Fill out your copyright notice in the Description page of Project Settings.


#include "EOSCreateSessionAsync.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

UEOSCreateSessionAsync* UEOSCreateSessionAsync::EOSCreateSessionAsync(
	FName sessionName,
	bool bIsDedicated = false,
	bool bIsLanMatch = false,
	int numPublicConnections = 2,
	bool bAllowJoinInProgress = true,
	bool bAllowJoinViaPresence = true,
	bool bUsesPresence = true
) {
	UEOSCreateSessionAsync* NewNode = NewObject<UEOSCreateSessionAsync>();

	NewNode->tempSessionName = sessionName;
	NewNode->tempIsDedicated = bIsDedicated;
	NewNode->tempIsLanMatch = bIsLanMatch;
	NewNode->tempNumPublicConnections = numPublicConnections;
	NewNode->tempAllowJoinInProgress = bAllowJoinInProgress;
	NewNode->tempAllowJoinViaPresence = bAllowJoinViaPresence;
	NewNode->tempUsesPresence = bUsesPresence;

	return NewNode;
}

void UEOSCreateSessionAsync::Activate()
{

	OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			FOnlineSessionSettings SessionSettings;

			SessionSettings.bIsDedicated = tempIsDedicated;
			//SessionSettings.bIsDedicated = true;
			SessionSettings.bIsLANMatch = tempIsLanMatch;
			SessionSettings.NumPublicConnections = tempNumPublicConnections;
			SessionSettings.bAllowJoinInProgress = tempAllowJoinInProgress;
			SessionSettings.bAllowJoinViaPresence = tempAllowJoinViaPresence;
			SessionSettings.bUsesPresence = tempUsesPresence;

			SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UEOSCreateSessionAsync::OnCreateSessionComplete);
			SessionPtr->CreateSession(0, tempSessionName, SessionSettings);

		}
	}
}

void UEOSCreateSessionAsync::OnCreateSessionComplete(FName sessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Create Session Status : %d"), bWasSuccessful);
	//UE_LOG(LogTemp, Warning, TEXT("SessionName : %s"), sessionName);

	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->ClearOnCreateSessionCompleteDelegates(this);
		}
	}
}