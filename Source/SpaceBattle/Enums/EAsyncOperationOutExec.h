#pragma once

#include "UObject/ObjectMacros.h"

UENUM()
enum EAsyncOperationOutExec {
	Waiting = 0,
	Success = 1,
	Failed = 2
};
