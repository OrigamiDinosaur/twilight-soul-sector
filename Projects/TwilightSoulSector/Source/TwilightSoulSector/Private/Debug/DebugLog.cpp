// Origami Dinosaur Creations 2026 (C)

#include "Debug/DebugLog.h"

DEFINE_LOG_CATEGORY(LogTss); 

//-----------------------------------------------------------------------------------------
// Public Static Functions:
//-----------------------------------------------------------------------------------------

void DebugLog::LogInfo(const FString Message) {
	UE_LOG(LogTss, Warning, TEXT("%s"), *Message);
	
}

void DebugLog::LogError(const FString Message) {
	UE_LOG(LogTss, Error, TEXT("%s"), *Message);
	
}