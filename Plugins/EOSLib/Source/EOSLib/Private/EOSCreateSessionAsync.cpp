// Fill out your copyright notice in the Description page of Project Settings.


#include "EOSCreateSessionAsync.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

UEOSCreateSessionAsync* UEOSCreateSessionAsync::EOSCreateSessionAsync(
	FName sessionName,
	bool bIsDedicated,
	bool bUseLobbiesIfAvailable,
	bool bIsLanMatch,
	bool bShouldAdvertise,
	int numPublicConnections,
	bool bAllowJoinInProgress,
	bool bAllowJoinViaPresence,
	bool bUsesPresence
) {
	UEOSCreateSessionAsync* NewNode = NewObject<UEOSCreateSessionAsync>();

	NewNode->tempSessionName = sessionName;
	NewNode->tempIsDedicated = bIsDedicated;
	NewNode->tempUseLobbiesIfAvailable = bUseLobbiesIfAvailable;
	NewNode->tempIsLanMatch = bIsLanMatch;
	NewNode->tempShouldAdvertise = bShouldAdvertise;
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
			SessionSettings.bUseLobbiesIfAvailable = tempUseLobbiesIfAvailable;
			SessionSettings.bIsLANMatch = tempIsLanMatch;
			SessionSettings.bShouldAdvertise = tempShouldAdvertise;
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

	if (bWasSuccessful)
	{
		OnSuccess.Broadcast(sessionName, bWasSuccessful);
		UE_LOG(LogTemp, Warning, TEXT("Session created"), 0);
	}
	else
	{
		OnFail.Broadcast(sessionName, bWasSuccessful);
		UE_LOG(LogTemp, Warning, TEXT("Session could not be created"), 0);
	}

	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->ClearOnCreateSessionCompleteDelegates(this);
		}
	}
}