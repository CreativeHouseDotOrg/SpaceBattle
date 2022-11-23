// Fill out your copyright notice in the Description page of Project Settings.


#include "EOSDestroySessionAsync.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

UEOSDestroySessionAsync* UEOSDestroySessionAsync::EOSDestroySessionAsync(
	FName sessionName
) {
	UEOSDestroySessionAsync* NewNode = NewObject<UEOSDestroySessionAsync>();

	NewNode->tempSessionName = sessionName;

	return NewNode;
}

void UEOSDestroySessionAsync::Activate()
{

	OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->OnDestroySessionCompleteDelegates.AddUObject(this, &UEOSDestroySessionAsync::OnDestroySessionComplete);
			SessionPtr->DestroySession(tempSessionName);

		}
	}
}

void UEOSDestroySessionAsync::OnDestroySessionComplete(FName sessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Destroy Session Status : %d"), bWasSuccessful);
	//UE_LOG(LogTemp, Warning, TEXT("SessionName : %s"), sessionName);

	if (bWasSuccessful)
	{
		OnSuccess.Broadcast(sessionName, bWasSuccessful);
		UE_LOG(LogTemp, Warning, TEXT("Session destroyed"), 0);
	}
	else
	{
		OnFail.Broadcast(sessionName, bWasSuccessful);
		UE_LOG(LogTemp, Warning, TEXT("Session could not be destroyed"), 0);
	}

	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->ClearOnDestroySessionCompleteDelegates(this);
		}
	}
}