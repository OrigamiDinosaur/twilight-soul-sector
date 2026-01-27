// Origami Dinosaur Creations 2026 (C)

#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTss, Log, All);

/*
 * Macros to print a message to the debug log:
 *
 * Usage:
 * 
 * LOG("Message to log.")
 * LOGPARAMS("Params: IsSprintingRequested = %d, DeltaTime = %f", IsSprintingRequested, DeltaTime); // logs a bool and a float.
 * LOGERROR & LOGERRORPARAMS - as above but logging them as errors not info.
 * LOGHEARTBEAT - logs a heartbeat message to a sub-folder.
 */

#define LOG(text) DebugLog::LogInfo(TEXT(text));
#define LOGERROR(text) DebugLog::LogError(TEXT(text));
#define LOGPARAMS(formatString, ...) DebugLog::LogInfo(FString::Printf(TEXT(formatString), ##__VA_ARGS__ ));
#define LOGERRORPARAMS(formatString, ...) DebugLog::LogError(FString::Printf(TEXT(formatString), ##__VA_ARGS__ ));

/*
 * Macros to print a message to the screen and debug log.
 *
 * Usage is as above.
 */
#define PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, text); UDebugLog::LogInfo(TEXT(text));
#define PRINTPARAMS(formatString , ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT(formatString), ##__VA_ARGS__ )); UDebugLog::LogInfo(FString::Printf(TEXT(formatString), ##__VA_ARGS__ ));

class TWILIGHTSOULSECTOR_API DebugLog {

	//-----------------------------------------------------------------------------------------
	// Public Static Functions:
	//-----------------------------------------------------------------------------------------

public:

	UFUNCTION(BlueprintCallable, Category = "Debug Log", meta = (DisplayName = "Log Info"))
	static void LogInfo(FString Message);

	UFUNCTION(BlueprintCallable, Category = "Debug Log", meta = (DisplayName = "Log Error"))
	static void LogError(FString Message);
};