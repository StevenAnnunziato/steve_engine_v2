#include "System_Win32.h"

// defined as an extern in System_Win32.h
HANDLE errorLogHandle;

// default constructor
SteveEngine::System::System()
{
    errorLogHandle = NULL;
}

void SteveEngine::System::Init()
{
    // set up hooks to check for memory leaks
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

    // init the console for debug output
    if (!AllocConsole())
    {
        SteveEngine::System::ShowError(ERROR_FAILED_INIT);
        ExitProcess(1);
    }

    freopen("CONOUT$", "w", stdout);
}
void SteveEngine::System::Shutdown()
{
    CloseHandle(errorLogHandle);
}

void SteveEngine::System::ShowError(const SteveEngine::string& message)
{
    MessageBox(NULL, message.c_str(), L"Error", MB_OK | MB_ICONERROR);
}
void SteveEngine::System::LogToErrorFile(const SteveEngine::string& message)
{
    // create new file if needed
    if (errorLogHandle == NULL)
        errorLogHandle = CreateFileW(L"GameErrors.txt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    auto len = (message + L"\n").size() * sizeof(SteveEngine::string::value_type);
    WriteFile(errorLogHandle, (message + L"\n").c_str(), len, NULL, NULL);
}