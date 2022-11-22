// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "EOSCreateSessionAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateSessionResponseDelegate, FName, SessionName, bool, bWasSuccessful);


/**
 * 
 */
UCLASS()
class SPACEBATTLE_API UEOSCreateSessionAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

protected: class IOnlineSubsystem* OnlineSubsystem;

private:
	UPROPERTY()
		FName tempSessionName;
	UPROPERTY()
		bool tempIsDedicated = false;
	UPROPERTY()
		bool tempIsLanMatch = false;
	UPROPERTY()
		int tempNumPublicConnections = 2;
	UPROPERTY()
		bool tempAllowJoinInProgress = true;
	UPROPERTY()
		bool tempAllowJoinViaPresence = true;
	UPROPERTY()
		bool tempUsesPresence = true;

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
		static UEOSCreateSessionAsync* EOSCreateSessionAsync(
			FName sessionName,
			bool bIsDedicated,
			bool bIsLanMatch,
			int numPublicConnections,
			bool bAllowJoinInProgress,
			bool bAllowJoinViaPresence,
			bool bUsesPresence
		);

	UPROPERTY(BlueprintAssignable)
		FCreateSessionResponseDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
		FCreateSessionResponseDelegate OnFail;

	virtual void Activate() override;
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	
};
