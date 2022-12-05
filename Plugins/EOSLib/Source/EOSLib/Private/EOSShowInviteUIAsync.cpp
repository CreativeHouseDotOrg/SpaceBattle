// Fill out your copyright notice in the Description page of Project Settings.


#include "EOSShowInviteUIAsync.h"

#include "OnlineSubsystem.h"
#include "Interfaces/OnlineExternalUIInterface.h"


UEOSShowInviteUIAsync* UEOSShowInviteUIAsync::EOSShowInviteUIAsync(FName sessionName) {
	UEOSShowInviteUIAsync* NewNode = NewObject<UEOSShowInviteUIAsync>();
	NewNode->tempSessionName = sessionName;
	return NewNode;
}

void UEOSShowInviteUIAsync::Activate()
{

	OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem)
	{
		if (IOnlineExternalUIPtr UIPtr = OnlineSubsystem->GetExternalUIInterface())
		{
			UIPtr->ShowInviteUI(0, tempSessionName);
		}
	}
}