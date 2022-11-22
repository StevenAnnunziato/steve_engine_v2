#pragma once

// win32 debug macros
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC // macro to make malloc give more info
#define WIN32_LEAN_AND_MEAN

#include "System_Common.h"
#include <Windows.h>
#include "SDL2/SDL.h"

extern HANDLE errorLogHandle;

// string constants for errors
const SteveEngine::string ERROR_K(L"Don't press k!!");
const SteveEngine::string ERROR_FAILED_INIT(L"Error: Failed to init the system console.");
const SteveEngine::string ERROR_LOAD_FILE(L"Error: loading a level data file failed.");
const SteveEngine::string ERROR_INVALID_COMPONENT(L"Error: read an invalid component ID while reading level data from disc.");