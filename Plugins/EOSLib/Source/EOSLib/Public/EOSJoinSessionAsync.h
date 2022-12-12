// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
#include "../Structs/FEOSFindSessionResultStruct.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "EOSJoinSessionAsync.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FJoinSessionResponseDelegate, FString, ConnectionInfo);

/**
 * 
 */
UCLASS()
class EOSLIB_API UEOSJoinSessionAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
	protected: class IOnlineSubsystem* OnlineSubsystem;

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
		static UEOSJoinSessionAsync* EOSJoinSessionAsync(FName SessionName, FEOSFindSessionResultStruct Session);
	
	virtual void Activate() override;

	FName tempSessionName;
	FEOSFindSessionResultStruct tempSession;
	
	UPROPERTY(BlueprintAssignable)
	FJoinSessionResponseDelegate OnSuccess;
	
	UPROPERTY(BlueprintAssignable)
	FJoinSessionResponseDelegate OnFail;
	
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
};
