// Fill out your copyright notice in the Description page of Project Settings.


#include "EOSGetFriendsAsync.h"

#include "Interfaces/OnlineFriendsInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

UEOSGetFriendsAsync* UEOSGetFriendsAsync::EOSGetFriendsAsync() {
	UEOSGetFriendsAsync* NewNode = NewObject<UEOSGetFriendsAsync>();
	return NewNode;
}

void UEOSGetFriendsAsync::Activate()
{

	OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem)
	{
		if (IOnlineFriendsPtr FriendsPtr = OnlineSubsystem->GetFriendsInterface())
		{
			FriendsPtr->ReadFriendsList(0, FString(""), FOnReadFriendsListComplete::CreateUObject(this, &UEOSGetFriendsAsync::OnReadFriendsListComplete));

		}
	}
}

void UEOSGetFriendsAsync::OnReadFriendsListComplete(int32 localUserNum, bool bWasSuccessful, const FString& listName, const FString& err)
{
	UE_LOG(LogTemp, Warning, TEXT("Getting Friends : %d"), bWasSuccessful);
	//UE_LOG(LogTemp, Warning, TEXT("SessionName : %s"), sessionName);

	if (OnlineSubsystem)
	{
		if (IOnlineFriendsPtr FriendsPtr = OnlineSubsystem->GetFriendsInterface())
		{
			TArray<TSharedRef<FOnlineFriend>> FriendsList;
			if (FriendsPtr->GetFriendsList(0, listName, FriendsList))
			{
				for (TSharedRef<FOnlineFriend> Friend : FriendsList)
				{
					FString FriendName = Friend.Get().GetRealName();
					UE_LOG(LogTemp, Warning, TEXT("Friend %s"), *FriendName)
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed getting Friends"), 0);
			}
		}
	}


	OnSuccess.Broadcast(localUserNum, bWasSuccessful, listName, err);
	UE_LOG(LogTemp, Warning, TEXT("Read Friends successfully"), 0);

	if (bWasSuccessful)
	{

	}
	else
	{
		OnFail.Broadcast(localUserNum, bWasSuccessful, listName, err);
		UE_LOG(LogTemp, Warning, TEXT("Could not read Friends"), 0);
	}
}