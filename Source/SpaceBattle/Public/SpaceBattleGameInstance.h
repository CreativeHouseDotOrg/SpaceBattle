// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SpaceBattleGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPACEBATTLE_API USpaceBattleGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:USpaceBattleGameInstance();

	virtual void Init() override;

	protected:
		class IOnlineSubsystem* OnlineSubsystem;

public:
	UFUNCTION(BlueprintCallable)
		void CreateSession();

public:
	UFUNCTION(BlueprintCallable)
		void Login();

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);
	
};
