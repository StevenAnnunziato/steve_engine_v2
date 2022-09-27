#pragma once

#include "System_Common.h"
#include <Windows.h>
#include "SDL2/SDL.h"

// win32 debug macros
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC // macro to make malloc give more info
#define WIN32_LEAN_AND_MEAN

HANDLE errorLogHandle; // is this a good way of doing this?

// declare string constants ??