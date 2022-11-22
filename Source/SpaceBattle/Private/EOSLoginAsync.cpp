// Fill out your copyright notice in the Description page of Project Settings.


#include "EOSLoginAsync.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

UEOSLoginAsync* UEOSLoginAsync::EOSLoginAsync() {
	UEOSLoginAsync* NewLoginNode = NewObject<UEOSLoginAsync>();
	return NewLoginNode;
}

void UEOSLoginAsync::Activate()
{

	OnlineSubsystem = IOnlineSubsystem::Get();



	if (OnlineSubsystem)
	{
		if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			FOnlineAccountCredentials Credentials;

			Credentials.Id = FString();
			Credentials.Token = FString();
			Credentials.Type = FString("accountportal");

			Identity->OnLoginCompleteDelegates->AddUObject(this, &UEOSLoginAsync::OnLoginComplete);

			// TODO
			// Outcome = EOutcomePins::Success;


			Identity->Login(0, Credentials);
		}
	}
}

void UEOSLoginAsync::OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Err)
{
	UE_LOG(LogTemp, Warning, TEXT("LOGIN STATUS : %d"), bWasSuccessful);

	if (bWasSuccessful) 
	{
		OnSuccess.Broadcast(LocalUserNum, bWasSuccessful, UserId.ToString(), Err);
		
		UE_LOG(LogTemp, Warning, TEXT("Login successful!"), 0);
	}
	else
	{
		OnFail.Broadcast(LocalUserNum, bWasSuccessful, UserId.ToString(), Err);
		UE_LOG(LogTemp, Warning, TEXT("Login failed!"), 0);
	}


	if (OnlineSubsystem)
	{
		if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			Identity->ClearOnLoginCompleteDelegates(0, this);
		}
	}
}