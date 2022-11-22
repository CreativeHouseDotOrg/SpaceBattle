// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "EOSLogoutAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLogoutResponseDelegate, int32, LocalUserNum, bool, bWasSuccessful);

/**
 * 
 */
UCLASS()
class SPACEBATTLE_API UEOSLogoutAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

protected: class IOnlineSubsystem* OnlineSubsystem;

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
		static UEOSLogoutAsync* EOSLogoutAsync();

	UPROPERTY(BlueprintAssignable)
		FLogoutResponseDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
		FLogoutResponseDelegate OnFail;

	virtual void Activate() override;
	void OnLogoutComplete(int32 LocalUserNum, bool bWasSuccessful);

	
};
