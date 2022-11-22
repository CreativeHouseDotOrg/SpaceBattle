// Fill out your copyright notice in the Description page of Project Settings.


#include "EOSLogoutAsync.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

UEOSLogoutAsync* UEOSLogoutAsync::EOSLogoutAsync() {
	UEOSLogoutAsync* NewNode = NewObject<UEOSLogoutAsync>();
	return NewNode;
}

void UEOSLogoutAsync::Activate()
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

			Identity->OnLogoutCompleteDelegates->AddUObject(this, &UEOSLogoutAsync::OnLogoutComplete);

			Identity->Logout(0);
		}
	}
}

void UEOSLogoutAsync::OnLogoutComplete(int32 LocalUserNum, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("LOGOUT STATUS : %d"), bWasSuccessful);

	if (bWasSuccessful)
	{
		OnSuccess.Broadcast(LocalUserNum, bWasSuccessful);
		UE_LOG(LogTemp, Warning, TEXT("Logout successful!"), 0);
	}
	else
	{
		OnFail.Broadcast(LocalUserNum, bWasSuccessful);
		UE_LOG(LogTemp, Warning, TEXT("Logout failed!"), 0);
	}

	if (OnlineSubsystem)
	{
		if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			Identity->ClearOnLoginCompleteDelegates(0, this);
		}
	}
}