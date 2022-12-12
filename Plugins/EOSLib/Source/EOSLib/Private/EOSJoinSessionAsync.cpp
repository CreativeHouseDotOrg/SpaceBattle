// Fill out your copyright notice in the Description page of Project Settings.


#include "EOSJoinSessionAsync.h"

#include "Kismet/GameplayStatics.h"

UEOSJoinSessionAsync* UEOSJoinSessionAsync::EOSJoinSessionAsync(FName SessionName, FEOSFindSessionResultStruct Session) {
	UEOSJoinSessionAsync* NewNode = NewObject<UEOSJoinSessionAsync>();
	NewNode->tempSessionName = SessionName;
	NewNode->tempSession = Session;
	return NewNode;
}

void UEOSJoinSessionAsync::Activate()
{
	OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->OnJoinSessionCompleteDelegates.AddUObject(this, &UEOSJoinSessionAsync::OnJoinSessionComplete);
			SessionPtr->JoinSession(0, tempSessionName, tempSession.OnlineResult);
		}
	}
}

void UEOSJoinSessionAsync::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("Join Sessions Status : %d"));

	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			FString ConnectionInfo = FString();
			SessionPtr->GetResolvedConnectString(SessionName, ConnectionInfo);
			if (!ConnectionInfo.IsEmpty())
			{

				OnSuccess.Broadcast(ConnectionInfo);
				UE_LOG(LogTemp, Warning, TEXT("Session joined"));			
				UE_LOG(LogTemp, Warning, TEXT("ConnectionInfo is %s"), *FString(ConnectionInfo));				
			}
			else
			{
				OnFail.Broadcast("ConnectionInfo is Empty");
				UE_LOG(LogTemp, Warning, TEXT("Session could not be joined"));
			}
		}
	}
	


	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->ClearOnJoinSessionCompleteDelegates(this);
		}
	}
}