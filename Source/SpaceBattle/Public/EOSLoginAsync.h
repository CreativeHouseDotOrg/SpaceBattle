// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "EOSLoginAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FLoginResponseDelegate, int32, LocalUserNum, bool, bWasSuccessful, const FString&, UserId, const FString&, Err);

/**
 * 
 */
UCLASS()
class SPACEBATTLE_API UEOSLoginAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()


protected: class IOnlineSubsystem* OnlineSubsystem;

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
		static UEOSLoginAsync* EOSLoginAsync();

	UPROPERTY(BlueprintAssignable)
		FLoginResponseDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
		FLoginResponseDelegate OnFail;

	virtual void Activate() override;
	void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Err);

};
