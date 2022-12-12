// Fill out your copyright notice in the Description page of Project Settings.


#include "EOSFindSessionsAsync.h"

UEOSFindSessionsAsync* UEOSFindSessionsAsync::EOSFindSessionsAsync() {
	UEOSFindSessionsAsync* NewNode = NewObject<UEOSFindSessionsAsync>();
	return NewNode;
}

void UEOSFindSessionsAsync::Activate()
{
	OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SearchSettings = MakeShareable(new FOnlineSessionSearch());

			SearchSettings->MaxSearchResults = 50;
			
			SearchSettings->QuerySettings.Set(SEARCH_KEYWORDS, FString("SpaceBattleLobby"), EOnlineComparisonOp::Equals);
			SearchSettings->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
			
			SessionPtr->OnFindSessionsCompleteDelegates.AddUObject(this, &UEOSFindSessionsAsync::OnFindSessionsComplete);
			SessionPtr->FindSessions(0, SearchSettings.ToSharedRef());
		}
	}
}

void UEOSFindSessionsAsync::OnFindSessionsComplete(bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Find Sessions Status : %d"), bWasSuccessful);

	TArray<FEOSFindSessionResultStruct> SearchResult;
	
	if (bWasSuccessful)
	{
		for (int i = 0; i < SearchSettings->SearchResults.Num(); i++ )
		{
			FOnlineSessionSearchResult res = SearchSettings->SearchResults[i];
			FString sessionOwnerName = res.Session.OwningUserName;
			
			FEOSFindSessionResultStruct str;

			str.OnlineResult = res;
			
			str.SessionOwnerName = sessionOwnerName;
			str.SessionIdStr = res.GetSessionIdStr();
			str.PingInMs = res.PingInMs;
			SearchResult.Add(str);
		}
		
		OnSuccess.Broadcast(bWasSuccessful,SearchResult);
		UE_LOG(LogTemp, Warning, TEXT("Sessions found %d"), SearchSettings->SearchResults.Num());
	}
	else
	{
		OnFail.Broadcast(bWasSuccessful, SearchResult);
		UE_LOG(LogTemp, Warning, TEXT("Sessions could not be found"));
	}

	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->ClearOnFindSessionsCompleteDelegates(this);
		}
	}
}