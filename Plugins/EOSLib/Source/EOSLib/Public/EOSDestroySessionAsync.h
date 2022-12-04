// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "EOSDestroySessionAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDestroySessionResponseDelegate, FName, SessionName, bool, bWasSuccessful);


/**
 * 
 */
UCLASS()
class EOSLIB_API UEOSDestroySessionAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
protected: class IOnlineSubsystem* OnlineSubsystem;

private:
	UPROPERTY()
		FName tempSessionName;

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
		static UEOSDestroySessionAsync* EOSDestroySessionAsync(
			FName sessionName
		);

	UPROPERTY(BlueprintAssignable)
		FDestroySessionResponseDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
		FDestroySessionResponseDelegate OnFail;

	virtual void Activate() override;
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
};
