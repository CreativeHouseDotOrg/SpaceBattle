// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../Enums/EAsyncOperationOutExec.h"
#include "SpaceBattleGameInstance.generated.h"


//UENUM()
//enum EAsyncOperationOutExec {
//	Waiting = 0,
//	Success = 1,
//	Failed = 2
//};



/**
 * 
 */
UCLASS()
class SPACEBATTLE_API USpaceBattleGameInstance : public UGameInstance
{
	GENERATED_BODY()
	public:USpaceBattleGameInstance();

	virtual void Init() override;

	protected: class IOnlineSubsystem* OnlineSubsystem;

	public:
		UFUNCTION(BlueprintCallable)
			void CreateSession();

	public:
		UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Outcome", Latent))
			void Login(TEnumAsByte<EAsyncOperationOutExec>& Outcome);

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);
	
};
