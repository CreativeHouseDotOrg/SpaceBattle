#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"

#include "FEOSFindSessionResultStruct.generated.h"

USTRUCT(BlueprintType)
struct FEOSFindSessionResultStruct
{
		GENERATED_USTRUCT_BODY()

		FOnlineSessionSearchResult OnlineResult;

		//~ The following member variable will be accessible by Blueprint Graphs:
		// This is the tooltip for our test variable.
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EOS Find Session Search Result")
		FString SessionIdStr;
		
		//~ The following member variable will be accessible by Blueprint Graphs:
		// This is the tooltip for our test variable.
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EOS Find Session Search Result")
		int32 PingInMs;
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EOS Find Session Search Result")
		FString SessionOwnerName;

		//~ The following member variable will be not accessible by Blueprint Graphs:
		// int32 NativeOnlyMemberVariable;

		/**~
		* This UObject pointer is not accessible to Blueprint Graphs, but
		* is visible to UE4's reflection, smart pointer, and garbage collection
		* systems.
		*/
		UPROPERTY()
		UObject* SafeObjectPointer;
};
