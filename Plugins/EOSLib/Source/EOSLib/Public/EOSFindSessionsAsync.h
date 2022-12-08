// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "EOSFindSessionsAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFindSessionsResponseDelegate, bool, bWasSuccessful);

/**
 * 
 */
UCLASS()
class EOSLIB_API UEOSFindSessionsAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
	protected: class IOnlineSubsystem* OnlineSubsystem;

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
		static UEOSFindSessionsAsync* EOSFindSessionsAsync();
	
	virtual void Activate() override;

	TSharedPtr<FOnlineSessionSearch> SearchSettings;
	
	UPROPERTY(BlueprintAssignable)
	FFindSessionsResponseDelegate OnSuccess;
	
	UPROPERTY(BlueprintAssignable)
	FFindSessionsResponseDelegate OnFail;
	
	void OnFindSessionsComplete(bool bWasSuccessful);
};
