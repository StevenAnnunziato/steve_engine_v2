#pragma once

#include "System_Common.h"

#ifdef __EMSCRIPTEN__
	#include "System_Emscripten.h"
#else // for windows
	#include "System_Win32.h"
#endif
