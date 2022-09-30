#include "System_Emscripten.h"
#include <iostream>

// default constructor
SteveEngine::System::System()
{
    
}

void SteveEngine::System::Init()
{
    // nothing to init
}
void SteveEngine::System::Shutdown()
{
    // nothing to shut down
}

void SteveEngine::System::ShowError(const SteveEngine::string& message)
{
    SteveEngine::string alertCommand = "alert(\"" + message + "\")";
    emscripten_run_script(alertCommand.c_str());
}
void SteveEngine::System::LogToErrorFile(const SteveEngine::string& message)
{
    std::cout << message << std::endl; // c_str()?
}