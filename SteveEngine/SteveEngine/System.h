#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC // macro to make malloc give more info
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <Windows.h>

namespace SteveEngine
{

	typedef std::wstring string;

	class System
	{
	public:

		System();

		void Init();
		void Shutdown();

		void ShowError(const SteveEngine::string& message);
		void LogToErrorFile(const SteveEngine::string& message);

	private:
		HANDLE errorLogHandle;

	};

}