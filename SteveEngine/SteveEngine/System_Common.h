#pragma once

#include <string>

#ifdef _DEBUG
	#ifdef __EMSCRIPTEN__
		#define DBG_NEW new
	#else // windows debug
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
	// allocations to be of _CLIENT_BLOCK type
	#endif
#else // any platform release
	#define DBG_NEW new
#endif

namespace SteveEngine
{

#ifdef __EMSCRIPTEN__
	typedef std::string string;
#else // windows
	typedef std::wstring string;
#endif
	

	class System
	{
	public:

		System();

		void Init();
		void Shutdown();

		void ShowError(const SteveEngine::string& message);
		void LogToErrorFile(const SteveEngine::string& message);

	};

}