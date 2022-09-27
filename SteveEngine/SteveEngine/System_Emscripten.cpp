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
    // alert here
}
void SteveEngine::System::LogToErrorFile(const SteveEngine::string& message)
{
    std::cout << message.c_str() << std::endl; // cool to use c_str() here?
}