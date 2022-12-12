// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystem.h"

#include "../Structs/FEOSFindSessionResultStruct.h"

#include "Kismet/BlueprintAsyncActionBase.h"
#include "EOSFindSessionsAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFindSessionsResponseDelegate, bool, bWasSuccessful, const TArray<FEOSFindSessionResultStruct>&, SearchResult);

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
