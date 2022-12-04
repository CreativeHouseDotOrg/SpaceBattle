// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "EOSGetFriendsAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FGetFriendsResponseDelegate, int32, localUserNum, bool, bWasSuccessful, const FString&, listName, const FString&, err);


/**
 * 
 */
UCLASS()
class EOSLIB_API UEOSGetFriendsAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	protected: class IOnlineSubsystem* OnlineSubsystem;

	private:
		UPROPERTY()
			FName tempSessionName;

	public:

		UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
			static UEOSGetFriendsAsync* EOSGetFriendsAsync();

		UPROPERTY(BlueprintAssignable)
			FGetFriendsResponseDelegate OnSuccess;

		UPROPERTY(BlueprintAssignable)
			FGetFriendsResponseDelegate OnFail;

		virtual void Activate() override;
		void OnReadFriendsListComplete(int32 localUserNum, bool bWasSuccessful, const FString& listName, const FString& err);
	
};
