#pragma once

#include <string>

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


	};

}