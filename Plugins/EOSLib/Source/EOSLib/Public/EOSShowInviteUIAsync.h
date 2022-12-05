// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "EOSShowInviteUIAsync.generated.h"

/**
 * 
 */
UCLASS()
class EOSLIB_API UEOSShowInviteUIAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	protected:
		class IOnlineSubsystem* OnlineSubsystem;

	
	private:
		UPROPERTY()
		FName tempSessionName;
	
	public:
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
		static UEOSShowInviteUIAsync* EOSShowInviteUIAsync(FName sessionName);
	
	virtual void Activate() override;
	
};
