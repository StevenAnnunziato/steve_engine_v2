@echo off

Rem TODO: make emsdk submodule

cd C:\Program Files\emsdk
@call emsdk_env.bat
cd C:\Users\saann\source\repos\GPR-400-01\SteveEngine
if not exist build\html mkdir build\html
emcc -ISteveEngine SteveEngine\System_Emscripten.cpp SteveEngine\SteveEngine.cpp -sUSE_SDL=2 -o build\html\index.html
echo Build successful.
pause